module LSU #(
    parameter RANDOM_DELAY = 0
)(//处理好输据的大小和符号扩展，总线发出
    input  clk,
    input  rst,

    input  [31:0] mem_addr,
    input  [31:0] mem_wdata,
    input  mem_write,
    input  mem_read,
    input  mem_unsigned,
    input  size,                 // 1: word, 0: byte
    input  [31:0] lsu_rdata,   // 从内存读回的原始 32 位字
    output [31:0] mem_rdata_o, // 按 word/byte 选好并扩展后的结果
    
    
    output [31:0] lsu_addr,
    output [31:0] lsu_wdata,
    output [7:0]  lsu_wmask,
    output [1:0]  lsu_size,
    output lsu_send_ok
);

// 这是 CPU 内部的测试允许条件，不是存储器的 ready 信号。
reg [7:0] lsu_lfsr;
always @(posedge clk) begin
    if (rst)
        lsu_lfsr <= 8'hA5;
    else
        lsu_lfsr <= {lsu_lfsr[6:0],
            lsu_lfsr[7] ^ lsu_lfsr[5] ^ lsu_lfsr[4] ^ lsu_lfsr[3]};
end

assign lsu_send_ok = (RANDOM_DELAY == 0) || (lsu_lfsr[1:0] == 2'b00);

wire [1:0] byte_off = mem_addr[1:0];

// ---------- load ----------
wire [31:0] word_data = lsu_rdata;
wire [7:0]  byte_data = word_data[byte_off * 8 +: 8];

wire [31:0] load_data = size ? word_data :
                        (mem_unsigned ? {24'b0, byte_data}
                                      : {{24{byte_data[7]}}, byte_data});

assign mem_rdata_o = mem_read ? load_data : 32'b0;




//waddr 按 4 字节对齐，
// wdata 的第 i 个字节对应 wmask 的第 i 位。
// 所以 sb 要先把数据左移到正确的字节车道。
wire [31:0] store_data = size ? mem_wdata : (mem_wdata << (byte_off * 8));
wire [7:0]  store_mask = size ? 8'h0F : (8'h01 << byte_off);

// IDU 当前只支持 byte 和 word；半字编码留给未来的指令支持。
assign lsu_size  = size ? 2'b10 : 2'b00;
assign lsu_addr  = mem_addr;
assign lsu_wdata = store_data;
assign lsu_wmask = store_mask;

endmodule
