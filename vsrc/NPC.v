`ifndef NPC_RANDOM_DELAY
`define NPC_RANDOM_DELAY 0
`endif
module NPC #(
    parameter RANDOM_DELAY = `NPC_RANDOM_DELAY
)(
    input         clock,
    input         reset,
    output        io_ifu_reqValid,
    output [31:0] io_ifu_addr,
    input         io_ifu_respValid,
    input  [31:0] io_ifu_rdata,
    output        io_lsu_reqValid,
    output [31:0] io_lsu_addr,
    output [1:0]  io_lsu_size,
    output        io_lsu_wen,
    output [31:0] io_lsu_wdata,
    output [3:0]  io_lsu_wmask,
    input         io_lsu_respValid,
    input  [31:0] io_lsu_rdata,
    input  [4:0]  dbg_raddr,
    output [31:0] dbg_rdata,
    output [31:0] pc, npc,
    output        is_ebreak, inst_valid, wen,
    output [1:0]  next_state
);

// 内部信号保留原名；CPU 对外接口采用 SoC 规范。
wire clk = clock;
wire rst = reset;
reg [63:0] clkcycle;
reg [63:0] inst_count;
always@(posedge clk) begin
  if(rst) inst_count <= 64'd0;
  else if(inst_valid) begin
    inst_count <= inst_count +1'b1;
  end
end
always @(posedge clk) begin
    if (rst)
        clkcycle <= 64'd0;
    else
        clkcycle <= clkcycle + 64'd1;
end


wire [31:0] a0_value;
`ifndef SYNTHESIS
import "DPI-C" function void is_ebreak_dpi(input int trap_pc, input int trap_a0);
always @(posedge clk) begin
    
    if (!rst && is_ebreak)begin
        $display("cycles = %0d, instructions = %0d",
         clkcycle + 64'd1, inst_count + 64'd1);

        
        is_ebreak_dpi(pc, a0_value);
    end
end
`endif
wire [31:0] ifu_rdata = io_ifu_rdata;
wire [31:0] ifu_raddr;
wire [31:0] lsu_addr, lsu_wdata;
wire [7:0] lsu_wmask;
wire [1:0] lsu_size;
wire lsu_read, lsu_write;
wire [31:0] lsu_rdata = io_lsu_rdata;
wire ifu_reqValid, lsu_reqValid;
wire ifu_respValid = io_ifu_respValid;
wire lsu_respValid = io_lsu_respValid;

assign io_ifu_reqValid = ifu_reqValid;
assign io_ifu_addr = ifu_raddr;
assign io_lsu_reqValid = lsu_reqValid;
assign io_lsu_addr = lsu_addr;
assign io_lsu_size = lsu_size;
assign io_lsu_wen = lsu_write;
assign io_lsu_wdata = lsu_wdata;
assign io_lsu_wmask = lsu_wmask[3:0];

wire [31:0] inst;
wire lsu_send_ok;

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
reg [31:0] csr_rdata;
wire [11:0] csr_addr = inst[31:20];
wire is_csrrs;
always@(*)begin
  case(csr_addr)
    12'hf11:csr_rdata = 32'h79737978;
    12'hf12:csr_rdata = 32'h05f642ee;
    12'hb00:csr_rdata = clkcycle[31:0];
    12'hb80:csr_rdata = clkcycle[63:32];
    default:csr_rdata = 32'd0;
  endcase
end
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
    .next_state(next_state),
    .is_csrrs(is_csrrs)
);

IFU #(.RANDOM_DELAY(RANDOM_DELAY)) u_ifu(
    .clk(clk),
    .rst(rst),
    .npc(npc),
    .pc(pc),    
    .ifu_raddr(ifu_raddr),
    .ifu_rdata(ifu_rdata),
    .inst(inst),
    .inst_valid(inst_valid),
    .mem_read(lsu_read),
    .next_state(next_state),
    .ifu_respValid(ifu_respValid),
    .ifu_reqValid(ifu_reqValid),
    .mem_write(lsu_write),
    .lsu_respValid(lsu_respValid),
    .lsu_reqValid(lsu_reqValid),
    .lsu_send_ok(lsu_send_ok)
    
    
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
    .jalr_pc(jalr_pc),
    .csr_rdata(csr_rdata)
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
    .dbg_rdata(dbg_rdata),
    .a0_value(a0_value)
);

LSU #(.RANDOM_DELAY(RANDOM_DELAY)) u_lsu(
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
    .lsu_wmask(lsu_wmask),
    .lsu_size(lsu_size),
    .lsu_send_ok(lsu_send_ok)

);

endmodule
