module LSU (
    input clk,
    input rst,
    input [31:0] mem_addr,
    input [31:0] mem_wdata,
    input mem_write,
    input mem_read,
    input mem_unsigned,
    input size,              // 1: word, 0: byte
    output [31:0] mem_rdata
);
    import "DPI-C" function int pmem_read(input int raddr);
    import "DPI-C" function void pmem_write(input int waddr, input int wdata, input byte wmask);

    wire [1:0] byte_off = mem_addr[1:0];

    // ---------- load ----------
    wire [31:0] word_data = mem_read ? pmem_read(mem_addr) : 32'b0;
    wire [7:0]  byte_data = word_data[byte_off * 8 +: 8];//意思是“从 byte_off*8 位开始取 8 位”。

    wire [31:0] load_data = size ? word_data :
                            (mem_unsigned ? {24'b0, byte_data}
                                          : {{24{byte_data[7]}}, byte_data});

    assign mem_rdata = mem_read ? load_data : 32'b0;

    // ---------- store ----------
    // pmem_write 约定：waddr 按 4 字节对齐，
    // wdata 的第 i 个字节对应 wmask 的第 i 位。
    // 所以 sb 要先把数据左移到正确的字节车道。
    wire [31:0] store_data = size ? mem_wdata : (mem_wdata << (byte_off * 8));
    wire [7:0]  store_mask = size ? 8'h0F : (8'h01 << byte_off);

    always @(posedge clk) begin
        if (!rst && mem_write) begin
            pmem_write(mem_addr, store_data, store_mask);
        end
    end
endmodule

           