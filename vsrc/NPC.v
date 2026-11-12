module NPC(
    input clk,
    input rst,

    
    output [31:0] pc,          
    input [31:0] ifu_rdata,
    output [31:0] ifu_raddr,

    
    output [31:0] lsu_addr,    
    output [31:0] lsu_wdata,   
    output [7:0]  lsu_wmask,   
    output        lsu_read,
    output        lsu_write,
    input  [31:0] lsu_rdata,   

    
    input  [4:0]  dbg_raddr,
    output [31:0] dbg_rdata,

    
    output [31:0] npc,
    output        is_ebreak,
    output inst_valid,
    output [1:0] next_state,
    output wen,
    output reg ifu_reqValid,
    input  reg ifu_respValid,
    output reg lsu_reqValid,
    input  reg lsu_respValid

);

wire [31:0] inst;

wire [4:0] waddr;
wire [4:0] raddr1;
wire [4:0] raddr2;
wire [31:0] rdata1;
wire [31:0] rdata2;

wire [31:0] wdata;

wire [31:0] imm;
wire is_jalr;
wire [1:0] alu_op;
wire alu_src_imm;
wire [31:0] alu_result;
wire [31:0] memdata;
wire mem_read;
wire mem_unsigned;
wire size;
wire [31:0] jalr_pc;
wire [1:0] wb_sel;


IDU u_idu(
    .inst(inst),
    .rs1(raddr1),
    .rs2(raddr2),
    .rd(waddr),
    .reg_wen(wen),
    .imm(imm),
    .is_jalr(is_jalr),
    .alu_op(alu_op),
    .alu_src_imm(alu_src_imm),
    .mem_write(lsu_write),
    .mem_read(lsu_read),
    .mem_unsigned(mem_unsigned),
    .size(size),
    .wb_sel(wb_sel),
    .is_ebreak(is_ebreak),
    .inst_valid(inst_valid),
    .next_state(next_state)
);

IFU u_ifu(
    .clk(clk),
    .rst(rst),
    .npc(npc),
    .pc(pc),    
    .ifu_raddr(ifu_raddr),
    .ifu_rdata(ifu_rdata),
    .inst(inst),
    .inst_valid(inst_valid),
    .mem_read(lsu_read),
    .next_state(next_state)
    .ifu_respValid(ifu_respValid),
    .ifu_reqValid(ifu_reqValid),
    .mem_write(lsu_write),
    .lsu_respValid(lsu_respValid)
    
    
);

EXU u_exu(
    .is_jalr(is_jalr),
    .data1(rdata1),
    .data2(rdata2),
    .memdata(memdata),
    .alu_op(alu_op),
    .alu_src_imm(alu_src_imm),
    .imm(imm),
    .exudata(alu_result),
    .jalr_pc(jalr_pc)
);

WBU u_wbu(
    .is_jalr(is_jalr),
    .alu_result(alu_result),
    .load_data(memdata),
    .pc(pc),
    .npc(npc),
    .reg_wdata(wdata),
    .wb_sel(wb_sel),
    .jalr_pc(jalr_pc)
);

RegisterFile #(5, 32) u_regfile(
    .clk(clk),
    .raddr1(raddr1),
    .raddr2(raddr2),
    .wdata(wdata),
    .waddr(waddr),
    .rdata1(rdata1),
    .rdata2(rdata2),
    .wen(wen),
    .dbg_raddr(dbg_raddr),
    .dbg_rdata(dbg_rdata)
);

LSU u_lsu(
    .clk(clk),
    .rst(rst),
    .mem_addr(alu_result),
    .mem_wdata(rdata2),
    .mem_write(lsu_write),
    .mem_read(lsu_read),
    .mem_unsigned(mem_unsigned),
    .size(size),
    .lsu_rdata(lsu_rdata),
    .mem_rdata_o(memdata),
    .lsu_addr(lsu_addr),
    .lsu_wdata(lsu_wdata),
    .lsu_wmask(lsu_wmask)

);

endmodule
