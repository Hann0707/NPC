# ysyx NPC + SoC 仿真框架学习指南

> 基于当前工作区的 Makefile 和代码整理。本文描述的是当前工程的实现，不代表所有 ysyx 工程都采用相同结构。路径以 `~/ysyx-workbench` 为根目录；代码以后改变时，应该重新核对。

## 1. 先认识两条构建链

运行程序之前，需要准备两种完全不同的东西：

```text
目标程序构建：让 NPC 将来有指令可执行
  应用 .c + AM + klib +（benchmark 时的 libbench）
                      ↓ 编译、链接
                    目标 .elf
                      ↓ gen.sh 加入现成加载器
                    Flash .bin

仿真器构建：让电脑可以模拟 NPC 和 SoC
  NPC RTL + SoC RTL + 仿真 C++ + NVBoard
                      ↓ Verilator + C++ 编译器
                    obj_dir/sim

运行：
  Linux 执行 obj_dir/sim，并给它 .bin 路径
                      ↓
  sim 模拟 NPC + SoC；被模拟的 NPC 执行 .bin 中的程序
```

**目标程序运行在被仿真的 NPC 上；`obj_dir/sim` 运行在你的 Linux 电脑上。** 两者不是同一个程序，也不是同一个 `main()`。

## 2. 目录地图

```text
ysyx-workbench/
├── NPC/                         你的 NPC 仿真工程
│   ├── vsrc/                    处理器 RTL：NPC、IFU、IDU、EXU、LSU、WBU 等
│   ├── csrc/main.cpp            宿主机 C++ 仿真入口
│   ├── constr/SimTop.nxdc       NVBoard 引脚约束
│   ├── Makefile                 编译 obj_dir/sim
│   ├── build/auto_bind.cpp      约束脚本生成的文件，不要手改
│   └── obj_dir/sim              编译生成的仿真器
├── ysyxSoC/
│   ├── ready-to-run/minirv/ElaborateTop.v  SoC 仿真 RTL，包含 SimTop
│   ├── ready-to-run/minirv/gen.sh           组合目标 ELF 和现成加载器
│   └── perip/                   UART、Flash、GPIO、PSRAM 等 RTL/模型
├── abstract-machine/            AM 接口、NPC 平台运行时、构建规则和 klib
├── am-kernels/                  hello、cpu-tests、am-tests 等目标程序
├── archbench/                   性能测试程序和 libbench
└── nvboard/                     模拟开发板、引脚绑定脚本及图形库
```

## 3. 你的 `.c` 之外，目标程序需要什么？

以自己编写一个调用 `putch()`、读取时间并返回的程序为例：

1. **编译器和汇编器**：将 C 和汇编翻译成 NPC 可以执行的指令。当前 `minirv-ysyxsoc` 继承 `minirv-npc.mk`，使用 minirv 编译器包装工具和 RISC-V 工具链。
2. **AM 启动代码**：设置程序启动所需环境，最终调用 `_trm_init()`、应用 `main()`。NPC 不会直接理解 C 的 `main` 名字。
3. **NPC 平台实现**：`abstract-machine/am/src/riscv/npc/trm.c` 提供 UART 初始化、`putch()` 和 `halt()`；`timer.c` 提供时间接口；`ioe.c` 将 AM 设备接口分发给相应函数。
4. **klib**：提供程序使用的基础库函数，例如讲义提供的 `printf()` 实现。头文件是声明，最终还需要链接到实际实现。
5. **链接脚本和平台参数**：决定程序入口、代码/数据地址、栈和堆布局；当前目标平台的链接起点是 `0x80000000`。
6. **现成加载器和镜像生成脚本**：`gen.sh` 将链接好的 ELF 与预制镜像组合，使 NPC 从 Flash 启动后能装载目标程序。
7. **libbench（仅 ArchBench 等需要它的程序）**：提供 benchmark 的运行框架、输入选择、计时及结果处理；普通自写 C 程序不一定需要。

AM 是运行在 NPC 上的软件层，不是生成硬件时钟的电路。比如 `putch()` 最终通过 NPC 访问 UART 寄存器；`__am_timer_uptime()` 执行 CSR 指令读 `mcycle`，再把周期数转换成微秒。

## 4. 目标程序从源码变成镜像

以 `archbench/bench/100.blockchain` 为例：

```text
100.blockchain/Makefile
  NAME=blockchain，SRCS=main.c Blockchain.c Block.c sha256.c
       ↓ include $(BENCH_HOME)/Makefile
archbench/Makefile
  添加 libbench；选择 $(AM_HOME)/Makefile
       ↓
abstract-machine/Makefile
  收集程序 .o 和库；选择 scripts/$(ARCH).mk；链接 ELF
       ↓ ARCH=minirv-ysyxsoc
scripts/minirv-ysyxsoc.mk
  include minirv-npc.mk；image 时调用 gen.sh
       ↓
scripts/minirv-npc.mk → scripts/platform/npc.mk、scripts/isa/riscv.mk
  配置工具链、NPC 平台 AM 源文件、链接选项
       ↓
生成 blockchain-minirv-ysyxsoc.elf
       ↓ gen.sh：复制预制镜像，在固定位置写入目标 ELF
生成 blockchain-minirv-ysyxsoc.bin
```

`.elf` 是带入口和加载段信息的目标程序；此 SoC `.bin` 是**现成加载器 + 嵌入的 ELF 镜像**，不是仿真器。`gen.sh` 的输入是 ELF；它依赖自身目录下的 `hello-minirv-ysyxsoc.bin` 模板。重新生成镜像会使用模板中的加载器，不会因为修改了 `trm.c` 就重新编译这个加载器。

### `mainargs` 是什么？

AM 的 `_trm_init()` 会把 `mainargs` 交给应用 `main()`。ArchBench 支持 `test`、`train`、`ref`、`huge` 等输入规模；本地 README 说明 `test` 用于正确性测试，不计分。`am-tests` 则使用例如 `t` 选择时钟测试。

当前 `platform/npc.mk` 的 `insert-arg` 规则会先生成 image，再调用 `insert-arg.py` 在**生成的 bin**中找到参数占位符并写入参数。单独执行 `image` 不等于已经注入了 `mainargs`。这个脚本会改写目标 bin，且只查找第一个匹配的占位符；出现异常时要核对它是否命中了目标程序部分。

## 5. 仿真器从 RTL 和 C++ 怎么生成？

在 NPC 目录，当前 [Makefile](Makefile) 的默认目标是 `sim`：

```text
constr/SimTop.nxdc
       ↓ auto_pin_bind.py
build/auto_bind.cpp ───────────────────────────────┐
                                                   │
NVBoard 源码 → nvboard.a + SDL 库 ──────────────────┤
                                                   ▼
ElaborateTop.v + vsrc/*.v + ysyxSoC/perip/*.v/*.sv → Verilator
csrc/main.cpp + auto_bind.cpp + NVBoard/SDL ───────→ C++ 编译、链接
                                                   ↓
                                              obj_dir/sim
```

当前 Makefile：

- 指定 `--top-module SimTop`，它是**模块名**；模块定义在 NPC 目录外的 `ElaborateTop.v` 中，文件不必和约束文件放在一起。
- 用 `wildcard` 选取 `vsrc/*.v`，排除旧的 `vsrc/top.v` 和 `vsrc/ysyx_100025070.v`；再用 `find` 递归收集 `ysyxSoC/perip` 下的 `.v/.sv`。被传入的文件不代表其中每个模块都会在顶层实际实例化。
- 通过 `-I` 添加 UART、SPI 的 Verilog include 搜索目录；这与 C++ 的头文件搜索目录不是一回事。
- 传入 `--timescale`、`--no-timing` 和讲义要求的 `-D` 宏；`__UART_TO_CONSOLE__` 让 UART 的仿真辅助代码向命令行直接输出字符。
- 把 NVBoard 静态库作为库文件传给 Verilator，并链接 SDL 库。
- `-Wno-fatal` 表示警告不作为致命错误，不表示没有警告，也不表示功能正确。

`sim` 是 `.PHONY`：每次 `make sim` 都会调用 Verilator；Verilator 内部是否重新编译某些文件取决于生成的依赖。NVBoard 的 `nvboard.a` 被列为链接输入，库更新后应触发重新链接。`auto_bind.cpp` 当前直接依赖 NXDC 文件；如果只改了绑定脚本或板卡定义，不能假定它一定自动重新生成。

### 两种输出路径

```text
NPC 写 UART FIFO → RTL 的 $write → Linux 命令行
                 └→ UART TX 串行位 → NVBoard 解码 → NVBoard 窗口
```

命令行输出正常只说明字符到达 `$write` 位置；NVBoard 串行接收还需要 TX 绑定、发送和接收的位周期匹配。

## 6. `SimTop.nxdc` 和 `main.cpp` 如何配合？

当前 `constr/SimTop.nxdc` 指定顶层 `SimTop`，将 UART TX、GPIO LED、数码管和 GPIO 开关等端口与 NVBoard 引脚绑定。`auto_pin_bind.py` 将约束翻译为 C++ 函数 `nvboard_bind_all_pins(VSimTop*)`；`main.cpp` 创建 `VSimTop` 后调用它，再初始化 NVBoard。更改顶层端口名或位宽时，要同时核对 RTL、约束及 C++ 使用方式。

运行时 `main.cpp` 大致执行：

1. 用参数 `argv[1]` 打开目标 `.bin`；不传参数时尝试当前工作目录的 `flash.bin`。
2. 把文件读进 16 MiB 的 `flash_mem`；Flash RTL 通过 DPI 调用 `flash_read()` 获取数据。
3. 初始化 NVBoard 和 SimTop 输入，让 reset 保持 100 个周期。
4. 每次循环令 `clock` 和 `cpuClock` 同步低、高各一次并 `eval()`，随后调用一次 `nvboard_update()`。
5. NPC 从 Flash 的复位地址取指，先执行加载器，再执行目标程序。
6. 当 NPC 检测到 `ebreak`，通过 DPI 传出 PC 和 `a0`；C++ 按当前约定判断 GOOD/BAD TRAP。

当前主循环有 5 亿周期上限；成功后代码会保持 NVBoard 窗口更新，**但不再推进 CPU 时钟**。因此窗口仍开着不等于 NPC 仍在执行，GOOD TRAP 也不一定意味着进程自然退出。没有显式开启波形追踪时，不要把目录中已有旧 VCD 当作本次运行的新波形。

## 7. 从程序输出一个字符到底经过什么？

```text
NPC 上的应用调用 printf / putch
        ↓
AM 的 putch 等待 UART 状态并写 UART MMIO 寄存器
        ↓
NPC 执行 load/store → CPU 总线 → SoC 地址译码 → UART16550
        ↓
UART FIFO 接收字符
        ├── $write → 命令行
        └── 发送器 → SimTop UART TX → NVBoard 解码显示
```

`trm.c` 是要编译进目标程序的软件；UART RTL 是仿真器中的硬件模型。现成加载器和目标程序可能先后写同一个 UART 除数寄存器；后写入的配置会覆盖之前的配置。要看实际运行哪个阶段，而不是只看某一个源码文件。

## 8. 修改了什么，需要重新做什么？

| 修改内容 | 需要做什么 | 不要误解成 |
|---|---|---|
| 应用 `.c`、`timer.c`、`trm.c` | 重新构建目标程序 ELF 和 bin；若需 `mainargs`，重新执行插参 | 旧 bin 会自动更新 |
| AM 头文件、库源码 | 重新构建依赖的库并重新链接目标镜像；检查日志确认对象确实重编 | 每次递归 make 一定会重编所有对象 |
| `NPC/vsrc/*.v`、SoC 外设 RTL、`ElaborateTop.v` | 在 NPC 中 `make sim`，再运行原有兼容 bin | 必须重编所有目标 C 程序 |
| `NPC/csrc/main.cpp`、Flash DPI、ebreak 处理 | `make sim` 重新编译/链接仿真器 | 修改了目标程序中的 main |
| `constr/SimTop.nxdc` | `make sim`，确认自动绑定文件重新生成并链接 | 只保存 NXDC 窗口就已生效 |
| NVBoard 源码，例如 UART divisor | `make sim`，检查 `nvboard.a` 更新且 `obj_dir/sim` 重新链接 | 改了源码就改变了旧 sim |
| `ARCH`、编译器、编译参数或构建脚本 | 重新构建受影响产物，并检查对象是否真的更新；必要时谨慎强制重建 | 只改变量就一定会重建所有旧对象 |
| SoC `gen.sh` 或其基础加载器镜像 | 重新生成目标 bin；保留原始基础镜像并确认偏移/版本 | 现有 bin 会自动替换加载器 |
| 仅更换已有的兼容 `.bin` | 把新路径传给 `obj_dir/sim` | 必须重新编译仿真器 |
| 修改 344 MHz 的时间换算系数 | 重编 AM/benchmark 镜像；核对 mcycle 和综合结果 | 仿真器实际墙钟速度变成 344 MHz |

注意：`make clean` 会删除构建产物。NPC 的 `make clean` 删除 `obj_dir` 和 `build`；AM 或 benchmark 的 clean 可能删除其整个 build（包括其他架构产物）。先确认目标内容，不要把 clean 当成排错的第一步。现成 klib archive 可能是讲义提供的预编译库；当前源码中的部分函数可能仍是占位实现，清理或重建前尤其应先确认，不要无条件覆盖。

## 9. 一个从修改到运行的例子：100.blockchain

假设综合报告的 344 MHz 是本次评估采用的 NPC 频率，且 `mcycle` 每 CPU 周期递增：

```text
344 MHz = 每微秒 344 周期
AM uptime 微秒 = 64 位 mcycle 周期数 / 344
```

这估算的是按该频率运行的**目标硬件时间**，不是 Linux 电脑跑仿真的墙钟时间。如果实际工作频率或综合约束不同，需要重新核对。高—低—高读取可避免 32 位低半部进位时拼接不一致。

在改好 `timer.c` 后，构建目标程序（会更新构建产物）：

```bash
export AM_HOME=~/ysyx-workbench/abstract-machine
export BENCH_HOME=~/ysyx-workbench/archbench
export NVBOARD_HOME=~/ysyx-workbench/nvboard

cd ~/ysyx-workbench/archbench/bench/100.blockchain
make ARCH=minirv-ysyxsoc insert-arg mainargs=test
```

留意 `timer.c` 编译日志与任何 `error:`，不能只因为最后打印了 `mainargs=test` 就断定前面成功。确认生成的 ELF/bin 是本次产物，再运行：

```bash
~/ysyx-workbench/NPC/obj_dir/sim ./build/blockchain-minirv-ysyxsoc.bin
```

如近期修改过 RTL 或仿真 C++，先在 NPC 目录运行 `make sim`。先用 test 检查正确性，不将 test 分数当正式性能评分；评估规模按讲义选。benchmark 可能超过当前 5 亿仿真周期，需区分还在执行、遇到错误或已到周期上限。以上命令根据当前规则整理，本指南没有实际执行它们。

## 10. 把 Makefile 连接关系串起来

```text
【应用入口 Makefile】
hello/Makefile 或 100.blockchain/Makefile
  ├─ NAME：产物名字
  ├─ SRCS：应用源文件
  └─ include AM 或 BENCH 的 Makefile
       │
       ├─ benchmark：archbench/Makefile 加入 libbench
       ▼
【AM 通用规则】abstract-machine/Makefile
  ├─ ARCH=minirv-ysyxsoc → include scripts/minirv-ysyxsoc.mk
  ├─ 应用 .c/.S → 对象 .o
  ├─ 递归构建/链接 am、klib（以及 libbench）
  ├─ .o + .a + 链接脚本 → $(IMAGE).elf
  └─ image/insert-arg 等目标串起镜像和参数步骤
       │
       ▼
【架构与平台规则】
minirv-ysyxsoc.mk → minirv-npc.mk → isa/riscv.mk + platform/npc.mk
  ├─ 工具链、ISA/ABI、启动源码、链接地址
  ├─ image → 在 SoC 目录调用 gen.sh $(IMAGE).elf $(IMAGE).bin
  └─ insert-arg → 向生成的 bin 写入 mainargs
       │
       ▼
【镜像脚本】ysyxSoC/ready-to-run/minirv/gen.sh
  └─ 现成 loader 模板 + 目标 ELF → SoC .bin

【仿真器入口 Makefile】NPC/Makefile（独立的一条链）
  ├─ SimTop.nxdc → auto_pin_bind.py → auto_bind.cpp
  ├─ include nvboard.mk → nvboard.a、SDL 选项
  ├─ SimTop/SoC RTL + NPC RTL + 外设 RTL
  └─ Verilator + main.cpp + 绑定代码 + 库 → obj_dir/sim
       │
       ▼
【两条链在运行时汇合】
obj_dir/sim 路径/程序.bin → 读取 Flash → 执行加载器 → NPC 执行目标程序
```

`image`、`insert-arg`、`sim`、`run` 是不同 Makefile 中的目标，作用取决于你所在目录和读取的 Makefile：当前 NPC 的 `make sim` 只构建仿真器；`make run ARGS=...` 先构建再运行。AM 平台的 `run` 则先生成并插入参数，再调用平台配置的仿真器。当前 `minirv-ysyxsoc.mk` 和 `npc.mk` 都为 `image` 定义过配方，后者被覆盖时会有 make 警告；警告本身不代表最终构建成功或失败。

## 11. 常见故障定位

- `Failed to load flash.bin`：没有传 bin 路径，或当前目录没有默认文件；先检查路径与文件是否可读。
- 编译有 `error:`，后面仍出现生成镜像的文字：把本次构建视为失败，修复首个错误并重新构建；不要运行可能陈旧或不完整的产物。
- 源码改了但行为没变：核对运行路径、目标 bin 的时间和内容、库是否重编、`obj_dir/sim` 是否重链接；必要时看反汇编或运行时状态。
- 串口命令行正常、NVBoard 乱码：分开查 FIFO `$write` 与 TX 采样路径，核对加载器和目标程序各阶段的 UART 除数、NVBoard divisor 和 update 调用频率。
- 只看到 `loading...`：这是加载器的进度，不能证明目标程序已运行；观察 PC、总线及目标入口。
- 没有 GOOD/BAD TRAP：先确认目标程序真的执行到 ebreak、`a0` 值、DPI 连接和 C++ 退出/窗口逻辑。
- RTC 不再输出但窗口还在：检查是否达到仿真周期上限；窗口刷新循环不等于 CPU 继续运行。

## 12. 最重要的三句话

1. **编译目标程序**生成 NPC 要执行的 ELF/bin；**编译仿真器**生成宿主机执行的 `obj_dir/sim`。
2. 修改哪一层，就重建那一层及其下游产物；确认实际运行的不是旧文件。
3. 先用可观察证据区分“编译成功、加载成功、NPC 执行成功、串口显示成功”，再定位问题。
