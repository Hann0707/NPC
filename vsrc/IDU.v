module IDU(
    input [31:0] inst,
    output [4:0] rs1,
    output [4:0] rs2,
    output [4:0] rd,
    output [31:0] I_imm,
    output reg_wen,
    output mem_write,
    output mem_read,
    output mem_unsigned,
    output size,
    output reg is_jalr,
    output [1:0]alu_op,
    output [1:0] wb_sel,
    output alu_src_imm
);
wire[6:0] opcode = inst[6:0];
wire[2:0] funct3 = inst[14:12];
wire  is_addi;
assign rd = inst[11:7];
assign rs1 = inst[19:15];
assign rs2 = inst[24:20];
assign I_imm = {{21{inst[31]}},inst[30:20]};
assign wb_sel = is_jalr ? 2'b10 : (is_addi ? 2'b00 : 2'b01);





  assign is_addi = (opcode == 7'b0010011) & (funct3 == 3'b000);
  assign is_jalr = (opcode == 7'b1100111) & (funct3 == 3'b000);

  assign reg_wen = is_addi | is_jalr;
  assign alu_op = (is_addi | is_jalr) ? 2'b01 : 2'b00;
  assign alu_src_imm = is_addi | is_jalr;

  endmodule