module EXU (
    
    input is_jalr,
    input[31:0] data1,
    input[31:0] data2,
    input [31:0] memdata,
    input [31:0] PC,

    input [31:0]imm,
    output wdata,
    output PCnext
);


  
end
wire [31:0] a = imm+rs1data
assign PCnext = (is_jalr)?a:PC+4;





endmodule