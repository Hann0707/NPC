module IFU(
    
    
    input [7:0]PC,
    output reg [31:0]PC,
    output [31:0]inst
);
reg [31:0] pc_reg ;
always@(posedge clk)begin
    if(rst) pc_reg <= 31'd0;
    else    pc_reg <=npc;
end
assign pc = pc_reg;
assign inst = imem_rdata;
assign imem_addr = pc_reg;
assign imem_valid = 1'b1;

endmodule


