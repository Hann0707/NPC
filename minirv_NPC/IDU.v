module IDU(
    input [31:0] inst,
    input [31:0] raddr1,
    input [31:0] raddr2,
    
    output  [4:0] rs1,
    output [4:0] rs2,
    output [4:0] rd,
    output [31:0] imm,
    output wen_reg,
    output waddren_m,
    output raddren_m
    
    output reg is_jalr
);
wire[6:0] opcode = inst[6:0];
wire[2:0] funct3 = inst[14:12];
reg is_addi;
assign rd = inst[11:7];
assign rs1 = inst[19:15];
assign rs2 = inst[24:20];
assign I_imm = {21{inst[31]},inst[30:20]};
assign reg




always@(*)begin
  is_addi = (opcode == 7'b0010011) & (funct3 == 3'b000);
  is_jalr = (opcode == 7'b1100111) & (funct3 == 3'b000);
end
