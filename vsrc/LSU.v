module LSU (
    input clk,
    input rst,
    input [31:0] mem_addr,
    input [31:0] mem_wdata,
    input mem_write,
    input mem_read,
    input mem_unsigned,
    input size,
    output reg[31:0] mem_rdata
    
);
    import "DPI-C" function int pmem_read(input int raddr);
    import "DPI-C" function void pmem_write(input int waddr, input int wdata, input byte wmask);
    wire [1:0] wmask = mem_addr[1:0];
    wire [31:0] wdata = mem_wdata;
    wire [3:0] size_mask = size ? 4'b1111 : (4'b0001<<wmask);
    assign mem_rdata = mem_read ? (size? pmem_read(mem_addr):pmem_read(mem_addr) & (8'h000000ff<<wmask)) : 32'b0;
    always @(posedge clk) begin
        
        end else if (mem_write) begin
            pmem_write(mem_addr, wdata, size_mask);
        end
    end
  
endmodule
        
           