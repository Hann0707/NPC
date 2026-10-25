module top(
    input clk,
    input rst,
    output [31:0] npc,
    output [31:0] pc,
    output [31:0] inst,
    input [4:0] dbg_raddr,
    output [31:0] dbg_rdata,
    output is_ebreak
    );
wire [4:0] waddr;
wire [4:0] raddr1;
wire [4:0] raddr2;
wire [31:0] rdata1;
wire [31:0] rdata2;

wire wen;
wire [31:0]wdata;

wire [31:0]imm;
wire is_jalr;
wire [1:0]alu_op;
wire alu_src_imm;
wire [31:0]alu_result;
wire [31:0]memdata;


wire mem_write;
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
  .mem_write(mem_write),
  .mem_read(mem_read),
  .mem_unsigned(mem_unsigned),
  .size(size),
  .wb_sel(wb_sel),
  .is_ebreak(is_ebreak)

);
IFU u_ifu(
  .npc(npc),
  .rst(rst),
  .clk(clk),
  .inst(inst),
  .pc(pc)
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
RegisterFile#(5,32)u_regfile
(
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
import "DPI-C" function void npc_ebreak(input int pc);
always@(posedge clk)begin
  if(!rst && is_ebreak)begin
    npc_ebreak(pc);
  end
end
LSU u_lsu(
  .clk(clk),
  .rst(rst),
  .mem_addr(alu_result),
  .mem_wdata(rdata2),
  .mem_write(mem_write),
  .mem_read(mem_read),
  .mem_unsigned(mem_unsigned),
  .size(size),
  .mem_rdata(memdata)
);
  
endmodule

