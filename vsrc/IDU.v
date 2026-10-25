module IDU(
    input [31:0] inst,
    output [4:0] rs1,
    output [4:0] rs2,
    output [4:0] rd,
    output [31:0] imm,
    output reg_wen,
    output mem_write,
    output mem_read,
    output mem_unsigned,
    output size,
    output  is_jalr,
    output [1:0]alu_op,
    output [1:0] wb_sel,
    output alu_src_imm,
    output is_ebreak
    
    
);
wire[6:0] opcode = inst[6:0];
wire[2:0] funct3 = inst[14:12];
wire  is_addi;
wire  is_lui;
wire  is_add;
wire  is_lw;
wire  is_sw;
wire  is_lbu;
wire  is_sb;
wire [31:0] I_imm;
wire [31:0] U_imm;
wire [31:0] S_imm;
wire I_type = is_addi | is_jalr | is_lw | is_lbu;
wire U_type = is_lui;
wire S_type = is_sw | is_sb;

assign rd = inst[11:7];
assign rs1 = inst[19:15];
assign rs2 = inst[24:20];
assign I_imm = {{21{inst[31]}},inst[30:20]};
assign imm = I_type ? I_imm : (U_type ? U_imm : S_imm);
assign U_imm = {inst[31:12],12'b0};
assign wb_sel = is_jalr ? 2'b10 : ((is_addi | is_lui |is_add) ? 2'b00 : 2'b01);
assign is_ebreak = (opcode == 7'b1110011) & (funct3 == 3'b000) & (inst[31:20] == 12'b000000000001);
assign S_imm = {{21{inst[31]}},inst[30:25],inst[11:7]};
assign mem_write = (is_sw | is_sb);
assign mem_read = (is_lw | is_lbu);
assign mem_unsigned = is_lbu;
assign size = (is_lw | is_sw) ? 1'b1 : 1'b0; //1:word, 0:byte


  assign is_addi = (opcode == 7'b0010011) & (funct3 == 3'b000);
  assign is_jalr = (opcode == 7'b1100111) & (funct3 == 3'b000);
  assign is_lui = (opcode == 7'b0110111);
  assign is_add = (opcode == 7'b0110011) & (funct3 == 3'b000) & (inst[31:25] == 7'b0000000);
  assign is_lw = (opcode == 7'b0000011) & (funct3 == 3'b010);
  assign is_sw = (opcode == 7'b0100011) & (funct3 == 3'b010);
  assign is_lbu = (opcode == 7'b0000011) & (funct3 == 3'b100);
  assign is_sb = (opcode == 7'b0100011) & (funct3 == 3'b100);

  assign reg_wen = is_addi | is_jalr | is_lui | is_add | is_lw | is_lbu;
  assign alu_op = (is_addi | is_jalr |is_add | is_lw | is_lbu| is_sb|is_sw) ? 2'b01 : 2'b00;//00lui, 01加法
  assign alu_src_imm = (is_addi | is_jalr | is_lui | is_lw | is_lbu| is_sb|is_sw) ? 1'b1 : 1'b0;//第二操作数是imm

  endmodule