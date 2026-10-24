#include<stdio.h>
#include<stdint.h>
#include <stdlib.h>
 uint32_t PC = 0;
 uint32_t R[32] = {0};
 uint8_t M[1000] = {
   
};

 void inst_cycle (int *end){
    uint32_t inst = ((uint32_t)M[PC+3] << 24) |((uint32_t)M[PC+2] << 16) | ((uint32_t)M[PC+1] << 8) | (uint32_t)M[PC];
    
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
        if(rd != 0){
            R[rd] = next_pc;
        }
        PC = (R[rs1] + imm) & ~1;           
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
        if(rd!=0){
            uint32_t b = R[rs1] + imm;
            R[rd] = (uint32_t)M[b] | ((uint32_t)M[b+1] << 8)
      | ((uint32_t)M[b+2] << 16) | ((uint32_t)M[b+3] << 24);

        }
    }
    else if(is_sw){
        PC_jump_flag = 0;
        uint32_t a =  R[rs1] + S_imm;
            M[a] = R[rs2] & 0xff;
            M[a+1] = (R[rs2] >> 8) &0xff;
            M[a+2] = (R[rs2] >> 16) &0xff;
            M[a+3] = (R[rs2] >> 24) & 0xff;
        
    }
    else if(is_lbu){
         PC_jump_flag = 0;
         if(rd!=0){
            R[rd] = (M[R[rs1] + imm]) & 0x000000ff;
         }
    }
    else if(is_sb){
        PC_jump_flag = 0;
        M[R[rs1] + S_imm] = R[rs2]&0xff;
    }
    else if(inst == 0x00100073){
        *end = 1;
    }

    if(PC_jump_flag == 0){
        PC = PC+4;
    }
    
}
int main(){
while(1){
    int end = 0;
    inst_cycle(&end);
    if(end == 1){
        printf("end\n");
        break;
    }

}


}