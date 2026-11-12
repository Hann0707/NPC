#include "Vtop.h"
#include "verilated.h"
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>//为了用rand函数
#include <sys/time.h>

extern "C"{
    uint32_t uart_status = 0;
}
extern "C" {
    long long hi;
    long long lo;
}
static uint8_t mem[128 << 20];
static uint32_t mem_base = 0x80000000u;
static uint32_t mem_size = sizeof(mem);
static bool is_ebreak = false;
bool emu_load_bin(const char *path);
void inst_cycle (int *end);
uint32_t *get_ref();
uint32_t get_pc();
uint8_t *get_mem();
static struct timeval root;
static uint64_t sim_cycle = 0;
static const uint64_t NPC_FREQ = 463ULL * 1000 * 1000;
unsigned long long get_time(){
   return sim_cycle / (NPC_FREQ / 1000000);
}
int check_regs(uint32_t *dut_ptr, uint32_t *ref_ptr)//检查寄存器是否一致
{
    bool is_diff = 0;

    for (int i = 0; i < 16; i++) {
        
        if (dut_ptr[i] != ref_ptr[i]) {
            printf("r%d different: dut=0x%08x ref=0x%08x\n", i, dut_ptr[i], ref_ptr[i]);
            is_diff = 1;
        }
    }

    return is_diff;
}

static uint32_t dbgpc= 0;
    extern "C" void pmem_write(int waddr, int wdata ,char wmask)//写内存函数, waddr是地址, wdata是数据, wmask是掩码
    {
        if(waddr<mem_base)
        {
            if(waddr == 0x10000000u){
                fputc(wdata & 0xff,stderr);
            }
            return;//其他mmio先忽略
        }
        if (waddr >= mem_base + mem_size) {
            return;// 超出内存范围
        }
    else {
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
}
 extern "C" void npc_ebreak(int pc){
    is_ebreak = true;
    dbgpc =  (uint32_t)pc;
}
 extern "C" int pmem_read(int addr)
 {
    
    uint32_t raddr = (uint32_t)addr - mem_base;
    
    if (addr == 0x10000004u) {  // 读出UART状态
        uart_status = (rand() & 0x7) == 0 ? 1 : 0; // 就绪概率为12.5%
        return (int)uart_status;
            
    }
    else if(addr == 0x20000000u){
        lo = get_time() & 0xffffffffu;
        
        return lo;
    }
    else if(addr == 0x20000004u){
        
        hi = get_time()>>32;
        return hi;
    }

    if (addr < mem_base || addr >= mem_base + mem_size) {
      
      return 0;
    }
    uint32_t off = raddr & ~3u;//抹掉低两位
    return mem[off] | (mem[off + 1] << 8) | (mem[off + 2] << 16) | (mem[off + 3] << 24);//小端序读取内存
    
 }
 //假如data = 0x12345678, addr = 0x00000000, 那么mem[0] = 0x78, mem[1] = 0x56, mem[2] = 0x34, mem[3] = 0x12
 static void load_word(uint32_t addr, uint32_t data) {
      for (int i = 0; i < 4; i++)
          mem[addr - mem_base + i] = (data >> (8 * i)) & 0xff;//0xff就是取低8位,小端序放内存
  }
  // 在 load_word 后面加
static bool load_bin(const char *path) {
    FILE *fp = fopen(path, "rb");
    if (!fp) { perror("fopen"); return false; }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (size < 0 || (size_t)size > mem_size) { fclose(fp); return false; }
    size_t n = fread(mem, 1, (size_t)size, fp);   // 文件第0字节 -> mem[0]
    fclose(fp);
    printf("loaded %zu bytes to 0x%08x\n", n, mem_base);
    return n == (size_t)size;
}

  Vtop *top;
  int main(int argc, char **argv) {
    gettimeofday(&root, NULL);
    Vtop dut;
    top = &dut;
    const char *bin = (argc >1) ? argv[1] : "/home/utg/ysyx-workbench/am-kernels/tests/cpu-tests/build/dummy-minirv-npc.bin";
    if(!load_bin(bin))
    {
        
        
        return 1;
    }
    if(!emu_load_bin(bin))
    {
        
        return 1;
    }
    // 复位
    dut.rst = 1;
    dut.clk = 0; dut.eval();
    dut.clk = 1; dut.eval();
    dut.clk = 0; dut.eval();
    dut.rst = 0;

    // 运行到 ebreak
    long long maxcycle = 50000000000ll;
    long long cycle = 0;
    int end = 0;
    int is_diff = 0;
    uint32_t dut_regs[16];
   
    long long inst_count = 0;
    while (!(is_ebreak &&end)&& (cycle < maxcycle)) {
        bool will_commit =  (dut.next_state != 0b10 && dut.inst_valid);
             


    
    dut.clk = 1;
    dut.eval();

    dut.clk = 0;
    dut.eval();

    
    if (will_commit) {
        
        inst_cycle(&end);
        inst_count++;
        for (int i = 0; i < 16; i++) {
            dut.dbg_raddr = i;
            dut.eval();
            dut_regs[i] = (uint32_t)dut.dbg_rdata;
        }
        
        if(get_pc() != dut.pc){
            printf("PC different: dut.pc = 0x%08x, ref.pc = 0x%08x\n", (uint32_t)dut.pc, get_pc());
            is_diff = 1;
        }
        if(check_regs(dut_regs, get_ref())) {
            is_diff = 1;
        }
        if(is_ebreak != end){
            printf("ebreak different: dut.end = %d, ref.end = %d\n", is_ebreak, end);
            is_diff = 1;
        }
        
    }

        cycle++;
        sim_cycle++;
        if(is_diff){
            break;
        }
        
        
    }
    if (!is_diff && is_ebreak && end) {
        uint8_t *ref_mem = get_mem();
        if (memcmp(mem, ref_mem, mem_size) != 0) {
            for (uint32_t i = 0; i < mem_size; i++) {
                if (mem[i] != ref_mem[i]) {
                    printf("mem different at 0x%08x: dut=0x%02x ref=0x%02x\n",
                           mem_base + i, mem[i], ref_mem[i]);
                    break;
                }
            }
            is_diff = 1;
        }
    }
int ret  = 1;
    if (is_diff) {
        printf("HIT BAD TRAP\n");
    }
        else if(is_ebreak && end){
            
            dut.dbg_raddr = 10;
        dut.eval();
            if(dut.dbg_rdata == 0x0){
                printf("HIT GOOD TRAP\n");
                ret = 0;
            }
            else{
                printf("HIT BAD TRAP\n");
            }
        }
        else {
            
    printf("max cycle reached: pc = 0x%08x\n", (uint32_t)dut.pc);
        }
    for (int i = 1; i <= 15; i++) {
        dut.dbg_raddr = i;
        dut.eval();
        printf("x%-2d = 0x%08x\n", i, (uint32_t)dut.dbg_rdata);
    }
    printf("time = %llu us\n", get_time());
    printf("IPC = %.2f\n", (double)inst_count / cycle);
    return ret;
}
  
    
    


