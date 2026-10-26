#include "Vtop.h"
#include "verilated.h"
#include <cstdio>
#include <cstdint>
static uint8_t mem[1 << 20];
static uint32_t mem_base = 0x80000000u;
static uint32_t mem_size = sizeof(mem);
static bool is_ebreak = false;
static uint32_t dbgpc= 0;
    extern "C" void pmem_write(int waddr, int wdata ,char wmask){
        uint32_t off = (((uint32_t)waddr  - mem_base)) & ~3u;//抹掉低两位
        uint32_t data = (uint32_t)wdata;
        uint8_t mask = (uint8_t)wmask;
        for(int i = 0;i<4;i++){
            if(mask & (1 << i))//如果mask的第i位为1,就写入数据
            {
                mem[off + i] = (data >> (8 * i)) & 0xff;
            }
        }
    }
 extern "C" void npc_ebreak(int pc){
    is_ebreak = true;
    dbgpc =  (uint32_t)pc;
}
 extern "C" int pmem_read(int addr)
 {
    uint32_t raddr = (uint32_t)addr - mem_base;
    if (addr < mem_base || addr >= mem_base + mem_size) {
      
      return 0;
    }
    uint32_t off = raddr & ~3u;//抹掉低两位
    return mem[off] | (mem[off + 1] << 8) | (mem[off + 2] << 16) | (mem[off + 3] << 24);
    
 }
 //假如data = 0x12345678, addr = 0x00000000, 那么mem[0] = 0x78, mem[1] = 0x56, mem[2] = 0x34, mem[3] = 0x12
 static void load_word(uint32_t addr, uint32_t data) {
      for (int i = 0; i < 4; i++)
          mem[addr - mem_base + i] = (data >> (8 * i)) & 0xff;//0xff就是取低8位
  }
  Vtop *top;
  int main(int argc, char **argv) {
    Vtop dut;
    top = &dut;

    const uint32_t prog[] = {
        0x800000B7,  // 00: lui   x1, 0x80000
        0x20008093,  // 04: addi  x1, x1, 0x200
        0x00500113,  // 08: addi  x2, x0, 5
        0x00700193,  // 0c: addi  x3, x0, 7
        0x00310233,  // 10: add   x4, x2, x3
        0x0000A283,  // 14: lw    x5, 0(x1)
        0x0040A223,  // 18: sw    x4, 4(x1)
        0x0040A303,  // 1c: lw    x6, 4(x1)
        0x0080C383,  // 20: lbu   x7, 8(x1)
        0x0090C403,  // 24: lbu   x8, 9(x1)
        0x00A0C483,  // 28: lbu   x9, 10(x1)
        0x00B0C503,  // 2c: lbu   x10, 11(x1)
        0x00608023,  // 30: sb    x6, 0(x1)
        0x0000A583,  // 34: lw    x11, 0(x1)
        0x002080A3,  // 38: sb    x2, 1(x1)
        0x0010C603,  // 3c: lbu   x12, 1(x1)
        0x800006B7,  // 40: lui   x13, 0x80000
        0x05868693,  // 44: addi  x13, x13, 0x58
        0x00068767,  // 48: jalr  x14, 0(x13)
        0x07B00793,  // 4c: addi  x15, x0, 123   (应被跳过)
        0x00000013,  // 50: nop
        0x00000013,  // 54: nop
        0x00100073,  // 58: ebreak
    };

    for (unsigned i = 0; i < sizeof(prog) / sizeof(prog[0]); i++) {
        load_word(0x80000000u + 4 * i, prog[i]);
    }

    // 数据区
    load_word(0x80000200, 0x12345678);
    load_word(0x80000208, 0xAABBCCDD);

    // 复位
    dut.rst = 1;
    dut.clk = 0; dut.eval();
    dut.clk = 1; dut.eval();
    dut.clk = 0; dut.eval();
    dut.rst = 0;

    // 运行到 ebreak
    int maxcycle = 1000;
    int cycle = 0;
    while (!is_ebreak && cycle < maxcycle) {
        dut.clk = 1; dut.eval();
        dut.clk = 0; dut.eval();
        cycle++;
    }

    if (is_ebreak) {
        printf("ebreak at pc = 0x%08x, cycles = %d\n", dbgpc, cycle);
    } else {
        printf("max cycle reached: pc = 0x%08x\n", (uint32_t)dut.pc);
    }

    // 打印寄存器
    for (int i = 1; i <= 15; i++) {
        dut.dbg_raddr = i;
        dut.eval();
        printf("x%-2d = 0x%08x\n", i, (uint32_t)dut.dbg_rdata);
    }

    // 打印内存
    printf("mem[0x80000200] = 0x%08x\n", (uint32_t)pmem_read(0x80000200));
    printf("mem[0x80000204] = 0x%08x\n", (uint32_t)pmem_read(0x80000204));
    printf("mem[0x80000208] = 0x%08x\n", (uint32_t)pmem_read(0x80000208));

    return 0;
}

    
    


