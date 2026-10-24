
module WBU(
    input is_jalr,
    input [31:0] alu_result,
    
    input [31:0] load_data,
    input [31:0] pc,
    input [1:0] wb_sel,// 00: alu_result, 01: load_data, 10: pc+4
    output [31:0] npc,
    output [31:0] reg_wdata,
  input [31:0] jalr_pc
    
);
assign npc = (is_jalr) ? jalr_pc : pc + 32'd4;
assign reg_wdata = (wb_sel == 2'b00) ? alu_result : (wb_sel == 2'b01) ? load_data : pc + 32'd4;

endmodule



