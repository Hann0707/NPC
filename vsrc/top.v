module top(
    input clk,
    input rst,
    output [31:0] npc,
    output [31:0] pc,
    output [31:0] inst,
    input  [4:0]  dbg_raddr,
    output [31:0] dbg_rdata,
    output        is_ebreak
);

import "DPI-C" function int pmem_read(input int raddr);
import "DPI-C" function void pmem_write(input int waddr, input int wdata, input byte wmask);
import "DPI-C" function void npc_ebreak(input int pc);

wire [31:0] mem_addr;
wire [31:0] mem_wdata;
wire [7:0]  mem_wmask;
wire        mem_read;
wire        mem_write;
wire [31:0] mem_rdata;

NPC u_npc(
    .clk(clk),
    .rst(rst),
    .pc(pc),
    .inst(inst),
    .mem_addr(mem_addr),
    .mem_wdata(mem_wdata),
    .mem_wmask(mem_wmask),
    .mem_read(mem_read),
    .mem_write(mem_write),
    .mem_rdata(mem_rdata),
    .dbg_raddr(dbg_raddr),
    .dbg_rdata(dbg_rdata),
    .npc(npc),
    .is_ebreak(is_ebreak)
);


assign inst = pmem_read(pc);

//只有 mem_read 有效时才采样
assign mem_rdata = mem_read ? pmem_read(mem_addr) : 32'b0;

// 写内存和 ebreak 通知在时钟沿 开始
always @(posedge clk) begin
    if (!rst && mem_write) begin
        pmem_write(mem_addr, mem_wdata, mem_wmask);
    end
    if (!rst && is_ebreak) begin
        npc_ebreak(pc);
    end
end

endmodule
