module EXU (
    
    input is_jalr,
    input[31:0] data1,
    input[31:0] data2,
    input [31:0] memdata,
    
    input [1:0]alu_op,
    input alu_src_imm,
    input [31:0]imm,
    output [31:0] exudata,
    
    output [31:0] jalr_pc
);


  

assign jalr_pc = (imm+data1) & ~32'd1;

assign exudata = (alu_src_imm == 1'b1) ? ((alu_op == 2'b00)? imm : data1+imm) : data1+data2;






endmodule