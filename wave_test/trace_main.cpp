#include "Vtop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>

// 模拟 NPC 的物理内存：地址 0x80000000 对应 mem[0]。
static constexpr uint32_t MEM_BASE = 0x80000000u;
static constexpr uint32_t MEM_SIZE = 128u << 20;
static uint8_t mem[MEM_SIZE];

static bool is_ebreak = false;
static uint32_t ebreak_pc = 0;
static uint64_t sim_cycle = 0;
// 与原 main.cpp 保持相同的仿真计时频率。
static constexpr uint64_t NPC_FREQ = 463ULL * 1000 * 1000;

static uint64_t get_time_us() {
    return sim_cycle / (NPC_FREQ / 1000000);
}

// 将 bin 的第 0 个字节加载到 mem[0]。
static bool load_bin(const char *path) {
    FILE *fp = std::fopen(path, "rb");
    if (!fp) {
        std::perror("fopen");
        return false;
    }
    if (std::fseek(fp, 0, SEEK_END) != 0) {
        std::perror("fseek");
        std::fclose(fp);
        return false;
    }
    long size = std::ftell(fp);
    if (size <= 0 || static_cast<uint64_t>(size) > MEM_SIZE ||
        std::fseek(fp, 0, SEEK_SET) != 0) {
        std::fprintf(stderr, "Invalid binary size or seek failed: %s\n", path);
        std::fclose(fp);
        return false;
    }
    size_t n = std::fread(mem, 1, static_cast<size_t>(size), fp);
    std::fclose(fp);
    if (n != static_cast<size_t>(size)) {
        std::fprintf(stderr, "Could not read entire binary: %s\n", path);
        return false;
    }
    std::printf("Loaded %zu bytes at 0x%08x\n", n, MEM_BASE);
    return true;
}

// 这三个 C 接口由 top.v 的 DPI-C 调用。
extern "C" int pmem_read(int addr) {
    const uint32_t a = static_cast<uint32_t>(addr);
    if (a == 0x10000004u) {
        return (std::rand() & 0x7) == 0 ? 1 : 0;
    }
    if (a == 0x20000000u) return static_cast<int>(get_time_us());
    if (a == 0x20000004u) return static_cast<int>(get_time_us() >> 32);
    if (a < MEM_BASE || a >= MEM_BASE + MEM_SIZE) return 0;

    const uint32_t off = (a - MEM_BASE) & ~3u;
    const uint32_t data = static_cast<uint32_t>(mem[off]) |
                          (static_cast<uint32_t>(mem[off + 1]) << 8) |
                          (static_cast<uint32_t>(mem[off + 2]) << 16) |
                          (static_cast<uint32_t>(mem[off + 3]) << 24);
    return static_cast<int>(data);
}

extern "C" void pmem_write(int addr, int data, char wmask) {
    const uint32_t a = static_cast<uint32_t>(addr);
    const uint32_t value = static_cast<uint32_t>(data);
    const uint8_t mask = static_cast<uint8_t>(wmask);
    if (a == 0x10000000u) {
        std::fputc(value & 0xffu, stderr);
        return;
    }
    if (a < MEM_BASE || a >= MEM_BASE + MEM_SIZE) return;

    const uint32_t off = (a - MEM_BASE) & ~3u;
    for (int i = 0; i < 4; ++i) {
        if (mask & (1u << i)) {
            mem[off + i] = static_cast<uint8_t>(value >> (8 * i));
        }
    }
}

extern "C" void npc_ebreak(int pc) {
    is_ebreak = true;
    ebreak_pc = static_cast<uint32_t>(pc);
}

int main(int argc, char **argv) {
    const char *bin = argc > 1 ? argv[1] :
        "/home/utg/ysyx-workbench/am-kernels/tests/cpu-tests/build/dummy-minirv-npc.bin";
    if (!load_bin(bin)) return 1;

    // 必须在第一次 eval() 之前启用追踪。
    Verilated::traceEverOn(true);
    Vtop dut;
    VerilatedVcdC trace;
    dut.trace(&trace, 99);
    trace.open("top.vcd");
    uint64_t t = 0;

    // 每次改变时钟后先计算电路，再记录当前信号。
    dut.rst = 1;
    dut.clk = 0; dut.eval(); trace.dump(t++);
    dut.clk = 1; dut.eval(); trace.dump(t++); // 复位上升沿
    dut.clk = 0; dut.eval(); trace.dump(t++);
    dut.rst = 0;

    const uint64_t max_cycles = 1000000;
    while (!is_ebreak && sim_cycle < max_cycles) {
        dut.clk = 1; dut.eval(); trace.dump(t++);
        dut.clk = 0; dut.eval(); trace.dump(t++);
        ++sim_cycle;
    }

    // AM 测试使用 a0（x10）作为退出状态。
    dut.dbg_raddr = 10;
    dut.eval();
    const uint32_t a0 = static_cast<uint32_t>(dut.dbg_rdata);
    if (is_ebreak) {
        std::printf("ebreak at 0x%08x, a0 = 0x%08x, cycles = %llu\n",
                    ebreak_pc, a0, static_cast<unsigned long long>(sim_cycle));
        std::printf("%s\n", a0 == 0 ? "HIT GOOD TRAP" : "HIT BAD TRAP");
    } else {
        std::printf("Cycle limit reached: pc = 0x%08x, cycles = %llu\n",
                    static_cast<uint32_t>(dut.pc),
                    static_cast<unsigned long long>(sim_cycle));
    }
    std::printf("Waveform: top.vcd\n");
    dut.final();
    trace.close();
    return is_ebreak && a0 == 0 ? 0 : 1;
}
