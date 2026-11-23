#include "VSimTop.h"
#include "verilated.h"
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <nvboard.h>
#define k 10
void nvboard_bind_all_pins(VSimTop *top);

uint8_t flash_mem [16 * 1024 * 1024] = {0};
bool is_ebreak = false;
uint32_t a0 = 0;
uint32_t pc = 0;
extern "C" void flash_read(int32_t addr, int32_t *data) {
    int32_t raddr = addr & ~3u;
    *data = (flash_mem[raddr + 0]  ) | (flash_mem[raddr + 1] << 8) | (flash_mem[raddr + 2] << 16) | (flash_mem[raddr + 3] << 24);
    
}
extern "C" void is_ebreak_dpi(int32_t pcc, int32_t a00){
    is_ebreak = true;
    pc = (uint32_t)pcc;
    a0 = (uint32_t)a00;
}
static bool load_bin(const char *path){
    FILE *fp = fopen(path,"rb");
    if(!fp) return false;
    fseek(fp,0,SEEK_END);
    long size=ftell(fp);
    fseek(fp,0,SEEK_SET);
    if(size <0 || size > sizeof(flash_mem)){
        fclose(fp);
        return false;
    }
    size_t n = fread(flash_mem,1,size,fp);
    if(n != (size_t)size){
        fclose(fp);
        return false;
    }
    fclose(fp);
    return true;
}

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    VSimTop dut;
   
    const char *bin = (argc > 1) ? argv[1] : "flash.bin";
    if (!load_bin(bin)) {
        fprintf(stderr, "Failed to load %s\n", bin);
        return 1;
    }
    nvboard_bind_all_pins(&dut);
    nvboard_init();
    dut.clock = 0;
    dut.cpuClock = 0;
    dut.reset = 1;
    dut.coreSel = 0;
    dut.externalPins_mygpio_in = 0;
    dut.externalPins_uart0_rx = 1;
    int PLL_k = 0;
    for (uint64_t cycle = 0; cycle < 500000000000ULL ; ++cycle) {
        if (cycle == 100ull*k) dut.reset = 0;
        
        dut.cpuClock = !dut.cpuClock;
        PLL_k ++;
        bool soc_rising = false;
        if (PLL_k == k) {
            bool old_clock = dut.clock;
            dut.clock = !dut.clock;
            PLL_k = 0;

           
            soc_rising = !old_clock && dut.clock;
    }
        dut.eval();
        if(soc_rising){
            nvboard_update();
        }
        soc_rising = false;
        dut.cpuClock = !dut.cpuClock;
        PLL_k++;
        if (PLL_k == k) {
            bool old_clock = dut.clock;
            dut.clock = !dut.clock;
            PLL_k = 0;

           
            soc_rising = !old_clock && dut.clock;
    }
        dut.eval();
        if(soc_rising){
            nvboard_update();
        }
        if (is_ebreak) break;
    }
    dut.final();
    if (is_ebreak) {
        if (a0 == 0) {
            printf("HIT GOOD TRAP at pc = 0x%08x\n", (unsigned)pc);
           
        }
        else {fprintf(stderr, "HIT BAD TRAP at pc = 0x%08x, a0 = 0x%08x\n",
                (unsigned)pc, (unsigned)a0);
                return 1;
        }
    }
    else{
        printf("fail\n");
        return 1;
    }
    while (true) {
    nvboard_update();
}
    
    
   


}
