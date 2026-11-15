// ElaborateTop's core0 expects this module name and the SoC memory interface.
`ifndef NPC_RANDOM_DELAY
`define NPC_RANDOM_DELAY 0
`endif
module ysyx_00000000 (
    input clock, input reset,
    output io_ifu_reqValid, output [31:0] io_ifu_addr,
    input io_ifu_respValid, input [31:0] io_ifu_rdata,
    output io_lsu_reqValid, output [31:0] io_lsu_addr,
    output [1:0] io_lsu_size, output io_lsu_wen,
    output [31:0] io_lsu_wdata, output [3:0] io_lsu_wmask,
    input io_lsu_respValid, input [31:0] io_lsu_rdata
);
    NPC #(.RANDOM_DELAY(`NPC_RANDOM_DELAY)) u_npc (
        .clock(clock), .reset(reset),
        .io_ifu_reqValid(io_ifu_reqValid), .io_ifu_addr(io_ifu_addr),
        .io_ifu_respValid(io_ifu_respValid), .io_ifu_rdata(io_ifu_rdata),
        .io_lsu_reqValid(io_lsu_reqValid), .io_lsu_addr(io_lsu_addr),
        .io_lsu_size(io_lsu_size), .io_lsu_wen(io_lsu_wen),
        .io_lsu_wdata(io_lsu_wdata), .io_lsu_wmask(io_lsu_wmask),
        .io_lsu_respValid(io_lsu_respValid), .io_lsu_rdata(io_lsu_rdata)
    );
endmodule
