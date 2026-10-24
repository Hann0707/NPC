module IFU(
      input  clk,
      input  rst,
      input  [31:0] npc,

      output [31:0] pc,
      output [31:0] inst
  );
      reg [31:0] pc_reg;

      always @(posedge clk) begin
          if (rst) pc_reg <= 32'h8000_0000;   // 讲义规定
          else     pc_reg <= npc;
      end

      assign pc = pc_reg;

      
      import "DPI-C" function int pmem_read(input int raddr);

      assign inst = pmem_read(pc_reg);
  endmodule



