module RegisterFile #(ADDR_WIDTH = 1, DATA_WIDTH = 1) (
  input clk,
  input [4:0]raddr1,
  input [4:0] raddr2
  input [DATA_WIDTH-1:0] wdata,
  input [ADDR_WIDTH-1:0] waddr,
  output [31:0] rdata1,
  output [31:0] rdata2,
  input wen
);
  reg [DATA_WIDTH-1:0] rf [2**ADDR_WIDTH-1:0];
  always @(posedge clk) begin
    if (wen) rf[waddr] <= wdata;
  end
  assign rdata1 = rf[raddr1];
  assign rdata2 = rf[raddr2];