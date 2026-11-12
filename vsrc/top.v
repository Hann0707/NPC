module top(
    input clk,
    input rst,
    output [31:0] npc,
    output [31:0] pc,
    
    input  [4:0]  dbg_raddr,
    output [31:0] dbg_rdata,
    output        is_ebreak,
    output inst_valid,
    output wen,
    output [1:0] next_state
    
);

import "DPI-C" function int pmem_read(input int raddr);
import "DPI-C" function void pmem_write(input int waddr, input int wdata, input byte wmask);
import "DPI-C" function void npc_ebreak(input int pc);
wire [31:0] ifu_raddr;
reg [31:0] ifu_rdata;
wire [31:0] lsu_addr;
wire [31:0] lsu_wdata;
wire [7:0]  lsu_wmask;
wire        lsu_read;
wire        lsu_write;
reg [31:0] lsu_rdata;
wire [31:0] mem_rdata_o;
wire [31:0] mem_addr;
wire [31:0] mem_wdata;

NPC u_npc(
    .clk(clk),
    .rst(rst),
    .pc(pc),
    .ifu_raddr(ifu_raddr),
    .ifu_rdata(ifu_rdata),
    .lsu_addr(lsu_addr),
    .lsu_wdata(lsu_wdata),
    .lsu_wmask(lsu_wmask),
    .lsu_read(lsu_read),
    .lsu_write(lsu_write),
    .lsu_rdata(lsu_rdata),
    .dbg_raddr(dbg_raddr),
    .dbg_rdata(dbg_rdata),
    .npc(npc),
    .is_ebreak(is_ebreak),
    .inst_valid(inst_valid),
    .next_state(next_state),
    .wen(wen)
    .ifu_reqValid(ifu_reqValid),
    .ifu_respValid(ifu_respValid),
    .lsu_reqValid(lsu_reqValid),
    .lsu_respValid(lsu_respValid)

);






always @(posedge clk) begin
    if (!rst && lsu_read && next_state == 2'b10) begin
    lsu_rdata <= pmem_read(lsu_addr);
end
if(ifu_reqValid)begin
    ifu_rdata <= rst ? 32'b0 : pmem_read(ifu_raddr);
end
    if (!rst && lsu_write) begin
        pmem_write(lsu_addr, lsu_wdata, lsu_wmask);
    end
    if (!rst && is_ebreak) begin
        npc_ebreak(pc);
    end
end

endmodule
