module RegisterFile #(ADDR_WIDTH = 1, DATA_WIDTH = 1) (
  input clk,
  input [4:0]raddr1,
  input [4:0] raddr2,
  input [DATA_WIDTH-1:0] wdata,
  
  input [ADDR_WIDTH-1:0] waddr,
  output [31:0] rdata1,
  output [31:0] rdata2,
  input wen,
  input  [4:0]  dbg_raddr,
  output [31:0] dbg_rdata

);

  reg [DATA_WIDTH-1:0] rf [2**ADDR_WIDTH-1:0];
  always @(posedge clk) begin
    if (wen && waddr != 0) begin
      rf[waddr] <= wdata;
    end
    $display("x%0d <= %0d", waddr, wdata);
  end
  assign rdata1 = (raddr1 ==0) ? {DATA_WIDTH{1'b0}}:rf[raddr1];
  assign rdata2 = (raddr2 ==0) ? {DATA_WIDTH{1'b0}}:rf[raddr2];
  assign dbg_rdata = (dbg_raddr ==0) ? {DATA_WIDTH{1'b0}}:rf[dbg_raddr];
  endmodule
  