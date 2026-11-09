module LSU(
    input  clk,
    input  rst,

    input  [31:0] mem_addr,
    input  [31:0] mem_wdata,
    input  mem_write,
    input  mem_read,
    input  mem_unsigned,
    input  size,                 // 1: word, 0: byte

    input  [31:0] mem_rdata_i,   // 从内存读回的原始 32 位字
    output [31:0] mem_rdata_o,   // 按 byte/half 选好并扩展后的结果

    output [31:0] mem_addr_o,
    output [31:0] mem_wdata_o,
    output [7:0]  mem_wmask_o
);

wire [1:0] byte_off = mem_addr[1:0];

// ---------- load ----------
wire [31:0] word_data = mem_rdata_i;
wire [7:0]  byte_data = word_data[byte_off * 8 +: 8];

wire [31:0] load_data = size ? word_data :
                        (mem_unsigned ? {24'b0, byte_data}
                                      : {{24{byte_data[7]}}, byte_data});

assign mem_rdata_o = mem_read ? load_data : 32'b0;

// ---------- store ----------
// pmem_write 约定：waddr 按 4 字节对齐，
// wdata 的第 i 个字节对应 wmask 的第 i 位。
// 所以 sb 要先把数据左移到正确的字节车道。
wire [31:0] store_data = size ? mem_wdata : (mem_wdata << (byte_off * 8));
wire [7:0]  store_mask = size ? 8'h0F : (8'h01 << byte_off);

assign mem_addr_o  = mem_addr;
assign mem_wdata_o = store_data;
assign mem_wmask_o = store_mask;

endmodule
