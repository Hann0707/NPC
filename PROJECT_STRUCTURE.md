# NPC 工作目录结构与文件说明

本文档用于复习 `/home/utg/NPC` 这个工作目录：
每个文件是做什么的、模块之间怎么连接、仿真怎么跑、ECC 综合怎么接。

---

## 1. 项目一句话

这是一个 **单周期 RISC-V（minirv / rv32e）NPC**：

- RTL 在 `vsrc/`
- Verilator 仿真 + DPI-C 内存 + `minirvEMU` 参考模型做 difftest
- ECC 综合工程在 `/home/utg/ecc/NPC`，综合顶层是 `NPC`（不是 `top`）

---

## 2. 目录树

```text
/home/utg/NPC
├── Makefile                  # Verilator 仿真构建
├── .gitignore                # 忽略 obj_dir、可执行文件、波形、core 等
├── .gitattributes            # 统一 LF 换行
├── PROJECT_STRUCTURE.md      # 本文档
│
├── vsrc/                     # 可综合 RTL（核心）
│   ├── top.v                 # 仿真专用顶层：DPI-C、内存、UART、ebreak
│   ├── NPC.v                 # 可综合顶层：例化各模块
│   ├── IFU.v                 # 取指单元：PC 寄存器（正在改成总线状态机）
│   ├── IDU.v                 # 译码单元
│   ├── EXU.v                 # 执行单元（ALU）
│   ├── LSU.v                 # 访存单元（load/store 数据选择）
│   ├── WBU.v                 # 写回/下一 PC
│   └── regfile.v             # 寄存器堆
│
├── csrc/                     # C++ 仿真代码
│   ├── main.cpp              # Verilator 主程序：加载 bin、时钟、difftest
│   ├── minirvEMU.cpp         # 参考指令模拟器
│   └── output/               # 空目录，预留输出
│
├── obj_dir/                  # Verilator 生成物（自动生成，不要手改）
├── rtl_backup_20261108/      # 旧版 RTL 备份（参考用）
├── core.*                    # 崩溃转储（可删）
└── minirvEMU.exe             # 旧的独立可执行文件（当前流程不用）
```

---

## 3. 每个文件的作用

### 3.1 RTL 文件

#### `vsrc/top.v` —— 仿真专用顶层

**不要把它放进 ECC 的 filelist。**

它做四件事：

1. 声明 DPI-C 函数：
   - `pmem_read`
   - `pmem_write`
   - `npc_ebreak`
2. 例化 `NPC`。
3. 取指：当前是组合读 `inst = pmem_read(pc)`。
4. 数据访存：
   - 读：`mem_rdata = mem_read ? pmem_read(mem_addr) : 0`
   - 写：在 `posedge clk` 且 `mem_write` 时调用 `pmem_write`
5. 把 `is_ebreak` 转成 `npc_ebreak(pc)`。

它包含 DPI-C，**不可综合**，所以只用于 Verilator 仿真。

---

#### `vsrc/NPC.v` —— 可综合顶层

ECC 综合时 `top = "NPC"` 指的就是它。

它只做例化和连线，不含时序逻辑：

```text
IDU  ← inst
IFU  ← clk/rst/npc，输出 pc
EXU  ← 寄存器数据、立即数、ALU 控制
WBU  ← ALU 结果、load 数据、pc，输出 npc / 写回数据
RF   ← 读写端口 + 调试读端口
LSU  ← 地址、写数据、读写控制，输出 mem_* 和 mem_rdata_o
```

主要端口：

| 端口 | 方向 | 作用 |
|---|---|---|
| `clk`, `rst` | in | 时钟、复位 |
| `pc` | out | 当前 PC |
| `inst` | in | 当前指令 |
| `mem_addr` | out | 访存地址 |
| `mem_wdata` | out | 写数据 |
| `mem_wmask` | out | 写掩码 |
| `mem_read` | out | 读使能 |
| `mem_write` | out | 写使能 |
| `mem_rdata` | in | 读回数据 |
| `dbg_raddr` / `dbg_rdata` | in/out | 调试读寄存器 |
| `npc` | out | 下一条 PC |
| `is_ebreak` | out | 当前指令是否 ebreak |

---

#### `vsrc/IFU.v` —— 取指单元

当前版本：

- `pc_reg` 保存当前 PC；
- 复位到 `0x8000_0000`；
- 每个时钟沿 `pc_reg <= npc`；
- 输出 `pc = pc_reg`。

正在改造成总线式状态机：

- `idle`：`ifu_raddr = pc`，跳 `wait`
- `wait`：`ifu_rdata` 有效，作为指令执行，跳 `idle`

改造后它还会输出：

- `inst`：当前有效指令
- `inst_valid`：当前是否有有效指令

---

#### `vsrc/IDU.v` —— 译码单元

纯组合逻辑，从 `inst` 译出控制信号。

目前支持的指令：

| 指令 | 说明 |
|---|---|
| `addi` | 立即数加法 |
| `lui` | 加载高 20 位 |
| `add` | 寄存器加法 |
| `jalr` | 间接跳转 |
| `lw` | 字加载 |
| `sw` | 字存储 |
| `lbu` | 字节无符号加载 |
| `sb` | 字节存储 |
| `ebreak` | 结束仿真 |

输出：

- `rs1`, `rs2`, `rd`
- `imm`
- `reg_wen`
- `mem_read`, `mem_write`
- `mem_unsigned`, `size`
- `is_jalr`
- `alu_op`, `alu_src_imm`
- `wb_sel`
- `is_ebreak`

---

#### `vsrc/EXU.v` —— 执行单元

纯组合逻辑，目前只有加法：

```verilog
jalr_pc = (imm + data1) & ~1;
exudata = alu_src_imm ? ((alu_op == 0) ? imm : data1 + imm)
                      : data1 + data2;
```

- `alu_op == 2'b00`：直接输出立即数（`lui`）
- 其他：加法

---

#### `vsrc/LSU.v` —— 访存单元

纯组合逻辑。

**Load：**

- 从 `mem_rdata_i` 中按 `mem_addr[1:0]` 选字节；
- `size=1` 取整字；
- `size=0` 取字节；
- `mem_unsigned=1` 零扩展，否则符号扩展；
- 只有 `mem_read=1` 时才输出 load 数据。

**Store：**

- `size=1`：字写，`wmask=8'h0F`；
- `size=0`：字节写，先把数据左移到对应字节车道，`wmask=8'h01 << byte_off`。

---

#### `vsrc/WBU.v` —— 写回/下一 PC

纯组合逻辑。

```verilog
npc = is_jalr ? jalr_pc : pc + 4;

reg_wdata = (wb_sel == 2'b00) ? alu_result
          : (wb_sel == 2'b01) ? load_data
          : pc + 4;
```

- `wb_sel=00`：写 ALU 结果
- `wb_sel=01`：写 load 数据
- `wb_sel=10`：写 `pc+4`（`jalr` 的返回地址）

---

#### `vsrc/regfile.v` —— 寄存器堆

- 32 个 32 位寄存器；
- `x0` 恒为 0；
- 写端口在 `posedge clk`，`wen && waddr != 0` 时写；
- 两个组合读端口；
- 一个调试读端口 `dbg_raddr` / `dbg_rdata`，给 C++ difftest 用。

---

### 3.2 C++ 仿真文件

#### `csrc/main.cpp` —— Verilator 主程序

流程：

1. 加载 `.bin` 到 `mem[]`，基址 `0x80000000`；
2. 把同一个 bin 加载到 `minirvEMU` 的参考内存；
3. 复位 3 个 eval；
4. 循环：
   - `clk=1; eval();`
   - `clk=0; eval();`
   - `inst_cycle(&end);` 让参考模型执行一条指令；
   - 读 DUT 寄存器；
   - 比较 PC、寄存器、`is_ebreak`；
   - 比较内存（结束时）；
5. 根据 `a0` 判断 `HIT GOOD TRAP` / `HIT BAD TRAP`；
6. 打印 `time = ... us`。

关键点：

- `NPC_FREQ = 463 MHz`；
- `get_time()` 返回 `sim_cycle / 463` 微秒；
- `cycle` 和 `sim_cycle` 每个循环加 1；
- 当前 difftest 假设 **DUT 每个循环执行一条指令**。

---

#### `csrc/minirvEMU.cpp` —— 参考模拟器

- `PC` 从 `0x80000000` 开始；
- `R[32]` 寄存器；
- `M[128MB]` 内存；
- `inst_cycle()` 每次执行一条指令；
- 支持指令与 IDU 基本对应：`addi`、`jalr`、`add`、`lui`、`lw`、`sw`、`lbu`、`sb`、`ebreak`；
- MMIO：
  - `0x10000004`：UART 状态
  - `0x20000000/0x20000004`：模拟时间 low/high
- 提供 `get_ref()`、`get_pc()`、`get_mem()` 给 difftest 用。

---

#### `csrc/output/`

空目录，预留放日志/输出。

---

### 3.3 构建与配置

#### `Makefile`

```make
VSRC := $(wildcard vsrc/*.v)
CSRC := $(wildcard csrc/*.cpp)

sim:
	verilator --cc --exe --build -j 0 -Wall -Wno-fatal \
	  --top-module top $(VSRC) $(CSRC) -o sim
	./obj_dir/sim
```

- 顶层模块：`top`
- 所有 `vsrc/*.v` 和 `csrc/*.cpp` 一起编译
- 生成 `obj_dir/sim`
- `make clean` 删除 `obj_dir`

#### `.gitignore`

忽略：

- `obj_dir/`
- `*.o`, `*.a`, `*.d`
- `sim`, `*.exe`
- 波形文件
- `core.*`
- 编辑器文件

#### `.gitattributes`

统一使用 LF，避免 Windows/Linux 换行差异；`*.exe` 等二进制不做转换。

---

### 3.4 生成物/辅助文件

| 路径 | 作用 |
|---|---|
| `obj_dir/` | Verilator 生成的 C++ 模型和构建产物；`make sim` 自动重建 |
| `rtl_backup_20261108/` | 旧版 `IFU.v`、`LSU.v`、`NPC.v` 备份，参考用 |
| `core.*` | 程序崩溃转储，可删 |
| `minirvEMU.exe` | 旧的独立可执行文件，当前 Makefile 不使用 |

---

## 4. 数据通路

```text
                 ┌──────────────┐
       npc ─────►│              │
                 │     IFU      │──── pc ───────────────┐
       clk ─────►│  pc_reg      │                       │
                 └──────────────┘                       │
                                                        ▼
                 ┌──────────────┐               ┌──────────────┐
       inst ────►│     IDU      │── control ──►│     EXU      │
                 │  decode      │               │  ALU         │
                 └──────┬───────┘               └──────┬───────┘
                        │ rd/rs1/rs2                    │ alu_result
                        ▼                              ▼
                 ┌──────────────┐               ┌──────────────┐
                 │  RegisterFile│◄── wdata ─────│     WBU      │
                 │  32x32       │               │  npc/wdata   │
                 └──────┬───────┘               └──────┬───────┘
                        │ rdata1/rdata2                 │ npc
                        │                              └──────► IFU
                        ▼
                 ┌──────────────┐
                 │     LSU      │── mem_addr/wdata/wmask/read/write ──► 内存
                 │ load/store   │◄──────────── mem_rdata ──────────────
                 └──────────────┘
```

### 当前单周期时序

```text
cycle N:
  pc_reg = PC
  inst  = mem[PC]          // 组合读
  IDU/EXU/LSU/WBU 全部组合计算
  npc   = next PC
posedge:
  pc_reg <= npc
  regfile 写
  mem 写
```

一条指令一个周期。

---

## 5. 仿真运行流程

### 5.1 构建并运行默认程序

```bash
cd /home/utg/NPC
make sim
```

`make sim` 会：

1. 调用 Verilator 生成 `obj_dir/`；
2. 编译 `csrc/*.cpp`；
3. 运行 `./obj_dir/sim`；
4. 默认加载：
   `/home/utg/ysyx-workbench/am-kernels/tests/cpu-tests/build/dummy-minirv-npc.bin`

也可以手动指定 bin：

```bash
./obj_dir/sim /path/to/program.bin
```

### 5.2 运行 hello

```bash
cd /home/utg/ysyx-workbench/am-kernels/tests/am-tests
make ARCH=minirv-npc mainargs=h run
```

`npc.mk` 里的 `run` 会调用：

```bash
/home/utg/NPC/obj_dir/sim build/amtest-minirv-npc.bin
```

### 5.3 运行 cpu-tests

```bash
cd /home/utg/ysyx-workbench/am-kernels/tests/cpu-tests
make ARCH=minirv-npc run
```

---

## 6. 程序是怎么跑起来的

```text
am-kernels 里的 C 程序
        ↓ 用 minirv-gcc 编译
abstract-machine 提供 start.S / trm.c / klib
        ↓ 链接到 0x80000000
.bin
        ↓ insert-arg.py 插入 mainargs
        ↓
/home/utg/NPC/obj_dir/sim
        ↓
top.v → NPC → IFU/IDU/EXU/WBU/LSU/regfile
```

关键接口：

- `putch` 写 `0x10000000`；
- 读 `0x10000004` 等 UART 状态；
- `halt(code)` 执行 `ebreak`，`a0=code`；
- `main.cpp` 的 `pmem_read` / `pmem_write` 模拟这些 MMIO。

---

## 7. ECC 综合工程

ECC 工程在：

```text
/home/utg/ecc/NPC/
├── ecc.toml
├── rtl/
│   ├── filelist.f        # 真正被读取的文件列表
│   ├── filelist.f.dir.bak
│   ├── NPC.v / IFU.v / ...（旧副本，不生效）
├── constraints/
└── runs/
```

`ecc.toml` 关键配置：

```toml
[design]
name = "NPC"
top = "NPC"
rtl = ["rtl/filelist.f"]
clock_port = "clk"
frequency_mhz = 100.0

[pdk]
name = "ics55"
root = "/home/utg/icsprout55-pdk"

[flow]
preset = "syn_sta"
run = "default"
```

`rtl/filelist.f` 指向真正的源文件：

```text
/home/utg/NPC/vsrc/NPC.v
/home/utg/NPC/vsrc/IFU.v
/home/utg/NPC/vsrc/IDU.v
/home/utg/NPC/vsrc/EXU.v
/home/utg/NPC/vsrc/WBU.v
/home/utg/NPC/vsrc/LSU.v
/home/utg/NPC/vsrc/regfile.v
```

注意：

- **不包含 `top.v`**，因为里面有 DPI-C，不可综合；
- 综合顶层是 `NPC`，不是 `top`；
- `rtl/` 里的其他 `.v` 是旧副本，只要不在 `filelist.f` 里就不参与综合。

运行：

```bash
cd /home/utg/ecc
./ecc run --project NPC --overwrite
```

`--overwrite` 会强制重新综合。

---

## 8. 当前 IFU 改造：从单周期取指到两状态总线取指

### 8.1 目标

```text
idle:
    ifu_raddr = pc
    next_state = wait

wait:
    ifu_rdata 有效
    inst = ifu_rdata
    next_state = idle
```

### 8.2 建议实现

```verilog
module IFU(
    input  clk,
    input  rst,
    input  [31:0] npc,

    output [31:0] ifu_raddr,
    input  [31:0] ifu_rdata,

    output [31:0] inst,
    output        inst_valid,
    output [31:0] pc
);

localparam IDLE = 1'b0;
localparam WAIT = 1'b1;

reg state, next_state;
reg [31:0] pc_reg;

// 状态寄存器
always @(posedge clk) begin
    if (rst) state <= IDLE;
    else     state <= next_state;
end

// 下一状态
always @(*) begin
    case (state)
        IDLE: next_state = WAIT;
        WAIT: next_state = IDLE;
        default: next_state = IDLE;
    endcase
end

// PC 只在指令有效时更新
always @(posedge clk) begin
    if (rst) pc_reg <= 32'h8000_0000;
    else if (state == WAIT) pc_reg <= npc;
end

assign ifu_raddr  = pc_reg;
assign pc         = pc_reg;
assign inst_valid = (state == WAIT);
assign inst       = inst_valid ? ifu_rdata : 32'h0000_0013; // NOP

endmodule
```

### 8.3 为什么要输出 NOP 和 inst_valid

在 `idle` 状态下，`ifu_rdata` 可能还是上一条指令或无效数据。如果直接把 `ifu_rdata` 接到 IDU：

- 可能重复写寄存器；
- 可能重复写内存；
- 如果上一条是 `ebreak`，可能错误触发 `npc_ebreak`。

所以：

- `idle` 时输出 NOP（`0x00000013`，即 `addi x0, x0, 0`）；
- 用 `inst_valid` 告诉寄存器堆和内存“这条指令才算数”。

更稳妥的写法是：

```verilog
wire wen_final       = wen       && inst_valid;
wire mem_write_final = mem_write && inst_valid;
```

把 `wen_final` 接到寄存器堆，`mem_write_final` 接到 LSU 和顶层。

### 8.4 时序

```text
clk       _/‾\_/‾\_/‾\_/‾\_
state     IDLE  WAIT  IDLE  WAIT
raddr     pc0   pc0   pc1   pc1
rdata     ---   inst0 ---   inst1
inst      NOP   inst0 NOP   inst1
valid     0     1     0     1
pc_reg    pc0   pc0   pc1   pc1
npc       pc1   pc1   pc2   pc2
```

`WAIT` 结束的那个上升沿：

- `pc_reg <= npc`；
- 寄存器堆写；
- 内存写；
- 状态回到 `IDLE`。

### 8.5 对 `main.cpp` 的影响

现有 `main.cpp` 每个循环都调用一次 `inst_cycle()`，并比较 PC/寄存器。  
改成两状态取指后，DUT **两个周期才执行一条指令**，参考模型会跑在前面，第一条指令就可能报：

```text
PC different: dut.pc = 0x80000000, ref.pc = 0x80000004
```

如果继续用 difftest，需要让 `main.cpp`：

- 只在 `inst_valid` 有效时调用 `inst_cycle()`；
- 在 DUT 提交后的 `IDLE` 周期比较 PC/寄存器/内存。

最小改法示意：

```cpp
if (dut.inst_valid) {
    inst_cycle(&end);       // WAIT 周期：参考模型执行当前指令
} else {
    // IDLE 周期：DUT 已提交上一条指令，此时比较
    // 读 dut_regs，比较 get_pc()/dut.pc，check_regs(...)
}
```

如果不改 `main.cpp`，这一版 FSM 会让 difftest 报错；这是两状态取指的必然结果，不是状态机写错了。

---

## 9. 常用命令速查

```bash
# 构建并运行默认测试
cd /home/utg/NPC
make sim

# 清理 Verilator 生成物
make clean

# 运行 hello
cd /home/utg/ysyx-workbench/am-kernels/tests/am-tests
make ARCH=minirv-npc mainargs=h run

# 运行 cpu-tests
cd /home/utg/ysyx-workbench/am-kernels/tests/cpu-tests
make ARCH=minirv-npc run

# ECC 综合
cd /home/utg/ecc
./ecc run --project NPC --overwrite
```

---

## 10. 复习要点

1. **`top.v` 是仿真顶层，`NPC.v` 是综合顶层。**
2. **DPI-C 只存在于 `top.v`，所以 ECC 不综合 `top.v`。**
3. **`NPC` 只做连线，时序在 `IFU` 和 `regfile`。**
4. **单周期时：一条指令一个周期，IPC = 1。**
5. **改成两状态取指后：一条指令两个周期，IPC ≈ 0.5。**
6. **difftest 的 `inst_cycle()` 必须和 DUT 的有效指令对齐。**
7. **ECC 只读 `rtl/filelist.f` 里列出的文件；`rtl/` 里的旧副本不生效。**
