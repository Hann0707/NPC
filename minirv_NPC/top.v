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
endmodule
module top(
    input clk,
    input rst,
    
    output PC,
    output W_Ram_addr,
    output R_Ram_addr,
    output W_Ram_en,
    output R_Ram_en

);
wire [5:0] waddr;
wire [5:0] raddr1;
wire [5:0] raddr2;
wire [31:0] rdata1;
wire [31:0] rdata2;
wire [31:0] PC;
wire wen;
wire [31:0]wdata;
wire [31:0]inst;


IDU u_idu(
  .clk (clk),
  .raddr1(raddr1),
  .raddr2(raddr2),
  .wen(wen),
  .waddr(waddr),
  .wdata(wdata),
  .rdata1(rdata1),
  .rdata2(rdata2)
);
IFU u_ifu(
  .PC(PC),
  .inst(inst),
  .PCout(PCout)
);
EXU u_exu(
  .is_addi(is_addi)
)

