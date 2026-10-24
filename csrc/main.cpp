#include "Vtop.h"
#include "verilated.h"
#include <cstdio>
#include <cstdint>
static uint8_t mem[1 << 20];
static uint32_t mem_base = 0x80000000u;
static uint32_t mem_size = sizeof(mem);
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
    load_word(0x80000000, 0x00100093);   // addi x1, x0, 1
    load_word(0x80000004, 0x00208113);   // addi x2, x1, 2
    load_word(0x80000008, 0x00310193);   // addi x3, x2, 3
    top ->rst = 1;
    top ->clk = 0;
    top ->eval();
    top ->clk = 1;
    top ->eval();
    top ->clk = 0;
    top ->eval();
    top ->rst = 0;
    for(int i = 0;i<3;i++){
        printf("cycle = %d, pc = :%08x, inst = %08x\n", i, top ->pc, top ->inst);
        for(int j = 0;j<4;j++){
            top->dbg_raddr = j;
            top->eval();
            printf("reg[%d] = %08x\n", j, top->dbg_rdata);
        }
        top ->clk = 1;
        top ->eval();
        top ->clk = 0;
        top ->eval();
    }
    for(int m = 0;m<4;m++){
            top->dbg_raddr = m;
            top->eval();
            printf("final,reg[%d] = %08x\n", m, top->dbg_rdata);
        }

    delete top;
      
      return 0;

  }
    
    


