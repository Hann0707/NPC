module IFU(
    input  clk,
    input  rst,
    input  [31:0] npc,
    output [31:0] pc
);

reg [31:0] pc_reg;

always @(posedge clk) begin
    if (rst) pc_reg <= 32'h8000_0000;
    else     pc_reg <= npc;
end

assign pc = pc_reg;

endmodule
