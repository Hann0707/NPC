// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"


class Vtop__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtop___024root final {
  public:

    // TOP LEVEL PORTS
    union {
        struct {
            VL_IN8(clk,0,0);
            VL_IN8(rst,0,0);
            VL_OUT(npc,31,0);
            VL_OUT(pc,31,0);
            VL_IN8(dbg_raddr,4,0);
            VL_OUT(dbg_rdata,31,0);
            VL_OUT8(is_ebreak,0,0);
            VL_OUT8(inst_valid,0,0);
            VL_OUT8(wen,0,0);
            VL_OUT8(next_state,1,0);
        } __VprimaryPorts;
    };

    // TRIVIALLY CONSTRUCTIBLE STATE
    ::CData/*0:0*/ top__DOT__u_npc__DOT__mem_read;
    ::CData/*7:0*/ top__DOT__u_npc__DOT__u_lsu__DOT__byte_data;
    ::CData/*0:0*/ top__DOT__u_npc__DOT__u_exu__DOT__is_jalr;
    ::CData/*1:0*/ top__DOT__u_npc__DOT__u_ifu__DOT__state;
    ::CData/*0:0*/ top__DOT__u_npc__DOT__u_idu__DOT__mem_write;
    ::CData/*0:0*/ top__DOT__u_npc__DOT__u_idu__DOT__mem_read;
    ::CData/*0:0*/ top__DOT__u_npc__DOT__u_idu__DOT__mem_unsigned;
    ::CData/*0:0*/ top__DOT__u_npc__DOT__u_idu__DOT__size;
    ::CData/*1:0*/ top__DOT__u_npc__DOT__u_idu__DOT__wb_sel;
    ::CData/*0:0*/ top__DOT__u_npc__DOT__u_idu__DOT__is_addi;
    ::CData/*0:0*/ top__DOT__u_npc__DOT__u_idu__DOT__is_add;
    ::CData/*0:0*/ top__DOT__u_npc__DOT__u_idu__DOT__is_lw;
    ::CData/*0:0*/ top__DOT__u_npc__DOT__u_idu__DOT__is_sw;
    ::CData/*0:0*/ top__DOT__u_npc__DOT__u_idu__DOT__S_type;
    ::CData/*0:0*/ __Vdfg_Regularize_146;
    ::CData/*0:0*/ __Vdfg_Regularize_147;
    ::CData/*0:0*/ __Vdfg_Regularize_150;
    ::CData/*0:0*/ __Vdfg_Regularize_151;
    ::CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    ::CData/*0:0*/ __Vtrigprevexpr___TOP__rst__0;
    ::CData/*4:0*/ __Vtrigprevexpr___TOP__dbg_raddr__0;
    ::CData/*0:0*/ __Vtrigprevexpr___TOP__clk__1;
    ::IData/*31:0*/ top__DOT____VlemCond_3;
    ::IData/*31:0*/ top__DOT____VlemCall_2__pmem_read;
    ::IData/*31:0*/ top__DOT____VlemCond_1;
    ::IData/*31:0*/ top__DOT____VlemCall_0__pmem_read;
    ::IData/*31:0*/ top__DOT__ifu_rdata;
    ::IData/*31:0*/ top__DOT__lsu_rdata;
    ::IData/*31:0*/ top__DOT__u_npc__DOT__u_exu__DOT__data1;
    ::IData/*31:0*/ top__DOT__u_npc__DOT__u_exu__DOT__data2;
    ::IData/*31:0*/ top__DOT__u_npc__DOT__u_exu__DOT__imm;
    ::IData/*31:0*/ top__DOT__u_npc__DOT__u_exu__DOT__exudata;
    ::IData/*31:0*/ top__DOT__u_npc__DOT__u_ifu__DOT__pc_reg;
    ::IData/*31:0*/ __Vdfg_Regularize_149;
    ::VlUnpacked<::IData/*31:0*/, 32> top__DOT__u_npc__DOT__u_regfile__DOT__rf;
    ::VlUnpacked<::QData/*63:0*/, 1> __VstlTriggered;
    ::VlUnpacked<::QData/*63:0*/, 2> __VicoTriggered;
    ::VlUnpacked<::QData/*63:0*/, 1> __VactTriggered;
    ::VlUnpacked<::QData/*63:0*/, 1> __VnbaTriggered;
    ::VlUnpacked<::CData/*0:0*/, 2> __VtraceActivity;

    // INTERNAL VARIABLES
    Vtop__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtop___024root(Vtop__Syms* symsp, const char* namep);
    ~Vtop___024root();
    VL_UNCOPYABLE(Vtop___024root);
    VL_UNMOVABLE(Vtop___024root);

    // INTERNAL METHODS
};


#endif  // guard
