
module WBU(
    input is_jalr,
    
    input [31:0]PC,
    input [31:0]rs1data,
    input [31:0] imm;
    input [31:0]alu_result,
    input wwen,
    input [4:0] rd,
    output wen,
    output[31:0] wdata,
    output reg[31:0]PCnext,
    output [5:0]waddr
    
);
wire [31:0] target = rs1data + imm; 
always@(*)begin
  if(is_jalr)begin
    PCnext = {target[31:1],1'b0};
  end
  else begin
    PCnext = PC+1'b1;
  end
end
assign wdata = alu_result;
assign waddr = rd;
assign wen = wwen;
endmodule


