#include<stdio.h>
#include<stdint.h>
#include <stdlib.h>
#include <cstdio>
#include <cstring>

uint32_t PC = 0x80000000;
 uint32_t R[32] = {0};
 uint8_t M[128 << 20];
 extern "C" uint32_t uart_status;
 extern "C" long long hi;
 extern "C" long long lo;
bool emu_load_bin(const char *path) {
    FILE *fp = fopen(path, "rb");
    if (!fp) { perror("fopen"); return false; }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (size <= 0 || (size_t)size > sizeof(M)) { fclose(fp); return false; }
    memset(M, 0, sizeof(M));

    size_t n = fread(M, 1, (size_t)size, fp);   // bin 第0字节 -> M[0] -> 0x80000000
    fclose(fp);

    PC = 0x80000000;
    for (int i = 0; i < 32; i++) R[i] = 0;
    return n == (size_t)size;
}
 
static uint8_t &MEM(uint32_t addr) {
    return M[addr - 0x80000000];
}
static bool is_mmio(uint32_t addr) {
    return addr <0x80000000 || addr >=0x80000000 + (128 << 20);   
}

 void inst_cycle (int *end) //end是一个指针，指向一个int类型的变量，用于标记是否遇到ebreak指令
 {
    uint32_t inst = ((uint32_t)MEM(PC+3) << 24) |((uint32_t)MEM(PC+2) << 16) | ((uint32_t)MEM(PC+1) << 8) | (uint32_t)MEM(PC);
    
    int32_t imm = (int32_t)inst >> 20;
    uint8_t rs1 = (inst >> 15) & 0x1F;
    uint8_t funct3 = (inst>>12) &0x7;
    uint8_t rd = (inst >> 7)& 0x1F;
    uint8_t opcode = (inst) &0x7F;
    uint32_t U_imm = inst & 0xfffff000;
    uint32_t funct7 = (inst >>25) & 0b1111111;
    uint32_t rs2  = (inst >> 20) & 0x1f;
    uint32_t S_imm = (int32_t)(((inst<<13) &0b00000001111100000000000000000000)|(inst&0b11111110000000000000000000000000))>>20;
    int is_addi = (opcode == 0b0010011) && (funct3 == 0b000);
    int is_jalr = (opcode == 0b1100111) &&(funct3 == 0b000);
    int is_add = (opcode == 0b0110011) && (funct3 == 0b000) &&(funct7 == 0b0000000);
    int is_lui = (opcode == 0b0110111);
    int is_sw = (opcode ==0b0100011) &&(funct3 == 0b010);
    int is_lw = (opcode == 0b0000011) && (funct3 == 0b010);
    int is_lbu = (opcode == 0b0000011) && (funct3 == 0b100 );
    int is_sb = (opcode == 0b0100011) && (funct3 == 0b000);
     

    int PC_jump_flag = 0;
    if(is_addi){
        PC_jump_flag = 0;
        if(rd != 0){
        R[rd] = R[rs1] + imm;
        
        }
    }
    else if(is_jalr){
        PC_jump_flag = 1;
        uint32_t next_pc = PC+4;      
        PC = (R[rs1] + imm) & ~1;   
        if(rd != 0){
            R[rd] = next_pc;
        }
                   
    }
    else if(is_add){
        PC_jump_flag = 0;
        if(rd != 0){
            R[rd] = R[rs1] +R[rs2];
        }
    }
    else if(is_lui){
        PC_jump_flag = 0;
        if(rd != 0){
            R[rd] = U_imm;
        }
    }
        else if(is_lw){
        PC_jump_flag = 0;
        if(rd != 0){
            uint32_t b = R[rs1] + imm;
            if (b == 0x10000004u){
                R[rd] = (uint32_t)uart_status;//与dut保持一致
            }
            else if(b == 0x20000000u){
                R[rd] = lo & 0xffffffffu;
            }
            else if(b == 0x20000004u){
                R[rd] = hi & 0xffffffffu;
            }
            else if(is_mmio(b)){
                R[rd] = 0;
            }
            else {
                R[rd] = (uint32_t)MEM(b) | ((uint32_t)MEM(b+1) << 8)
                      | ((uint32_t)MEM(b+2) << 16) | ((uint32_t)MEM(b+3) << 24);
            }
        }
    }
    else if(is_sw){
        PC_jump_flag = 0;
        uint32_t a = R[rs1] + S_imm;
        if(!is_mmio(a)){
            MEM(a)   = R[rs2] & 0xff;
            MEM(a+1) = (R[rs2] >> 8) & 0xff;
            MEM(a+2) = (R[rs2] >> 16) & 0xff;
            MEM(a+3) = (R[rs2] >> 24) & 0xff;
        }
    }
    else if(is_lbu){
        PC_jump_flag = 0;
        if(rd != 0){
            uint32_t b = R[rs1] + imm;
            if(b == 0x10000004u){
                R[rd] = (uint32_t)uart_status & 0xff;
            }
            else if(b == 0x20000000u){
                R[rd] = lo & 0xff;
            }
            else if(b == 0x20000004u){
                R[rd] = hi & 0xff;
            }
            else if(is_mmio(b)){ R[rd] = 0;}
            else R[rd] = MEM(b) & 0x000000ff;
        }
    }
    else if(is_sb){
        PC_jump_flag = 0;
        uint32_t a = R[rs1] + S_imm;
        if(!is_mmio(a)) MEM(a) = R[rs2] & 0xff;
    }
    else if(inst == 0x00100073){
        *end = 1;
    }

    if(PC_jump_flag == 0){
        PC = PC+4;
    }
}


 

uint32_t *get_ref(){
    return R;
}
uint32_t get_pc(){
    return PC;
}
uint8_t *get_mem(){
    return M;
}



