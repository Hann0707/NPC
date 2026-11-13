module IFU #(
    parameter RANDOM_DELAY = 0
)(
    input  clk,
    input  rst,
    input  [31:0] npc,//来自NPC的下一条指令地址
    output [31:0] ifu_raddr,
    input [31:0] ifu_rdata,
    output [31:0] pc,
    output [31:0] inst,
    output inst_valid,
    input mem_read,
    output reg [1:0] next_state,
    input ifu_respValid,
    output ifu_reqValid,
    input mem_write,
    input lsu_respValid,
    output lsu_reqValid,
    input lsu_send_ok
);

reg [31:0] pc_reg;//PC寄存器


//状态机

//状态定义
parameter idle = 2'b00;//空闲状态
parameter WAIT = 2'b01;//等待状态
parameter load_wait = 2'b10;//加载等待状态
localparam lsu_send = 2'b11;//请求尚未发出，等待允许发送
//当前状态和下一状态
reg [1:0] state;

// 等待期间也持续更新
reg [7:0] ifu_lfsr;
always @(posedge clk) begin
    if (rst)
        ifu_lfsr <= 8'h01;
    else
        ifu_lfsr <= {ifu_lfsr[6:0],
            ifu_lfsr[7] ^ ifu_lfsr[5] ^ ifu_lfsr[4] ^ ifu_lfsr[3]};
end

wire ifu_send_ok = (RANDOM_DELAY == 0) || (ifu_lfsr[1:0] == 2'b00);


//第一段：状态寄存器
always @(posedge clk) begin
    if(rst) begin
        state <= idle;
    end
    else begin
        state <= next_state;
    end
end

//第二段：状态转移逻辑
always @(*) begin
    case(state)
        idle :begin
            next_state = ifu_reqValid ? WAIT : idle;
        end
        WAIT :begin
            if(ifu_respValid == 1'b0) begin
                next_state = WAIT;
            end
            else begin
                if(mem_read ==1'b1 || mem_write == 1'b1) begin
                    next_state = lsu_reqValid ? load_wait : lsu_send;
                end
                else begin
                    next_state = idle;
                end
                
            end
        end
        lsu_send :begin
            next_state = lsu_reqValid ? load_wait : lsu_send;
        end
        load_wait :begin
            if(lsu_respValid == 1'b0) begin
                next_state = load_wait;
            end
            else begin
                next_state = idle;
            end
        end
        
        default :begin
            next_state = idle;
        end
    endcase
end


always @(posedge clk) begin
    if (rst)
        pc_reg <= 32'h80000000;
    else if (inst_valid)
        pc_reg <= npc;
end


    assign ifu_reqValid = !rst && (state == idle) && ifu_send_ok;
    // 能立即发送就保持原路径；否则由 lsu_send 记住尚未发送的请求。
    assign lsu_reqValid = !rst && lsu_send_ok &&
        (((state == WAIT) && ifu_respValid && (mem_read || mem_write)) ||
         (state == lsu_send));

    

    
    
    
//end
assign ifu_raddr = pc_reg;//发给指令存储器的读地址，本设计中等于pc_reg
assign pc = pc_reg;//当前pc，给cpu内部用 比如pc+4
assign inst = ifu_rdata;//指令存储器读出的指令，给cpu内部用
assign inst_valid =!rst &&((state == WAIT && ifu_respValid && !(mem_read || mem_write)) ||(state == load_wait && lsu_respValid));

//指令有效信号，给cpu内部用

endmodule
