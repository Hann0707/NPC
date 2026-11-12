// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"

extern "C" int pmem_read(int raddr);

void Vtop___024root____Vdpiimwrap_top__DOT__pmem_read_TOP(::IData/*31:0*/ raddr, ::IData/*31:0*/ &pmem_read__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root____Vdpiimwrap_top__DOT__pmem_read_TOP\n"); );
    // Body
    int raddr__Vcvt;
    raddr__Vcvt = raddr;
    int pmem_read__Vfuncrtn__Vcvt;
    pmem_read__Vfuncrtn__Vcvt = pmem_read(raddr__Vcvt);
    pmem_read__Vfuncrtn = (pmem_read__Vfuncrtn__Vcvt);
}

extern "C" void pmem_write(int waddr, int wdata, char wmask);

void Vtop___024root____Vdpiimwrap_top__DOT__pmem_write_TOP(::IData/*31:0*/ waddr, ::IData/*31:0*/ wdata, ::CData/*7:0*/ wmask) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root____Vdpiimwrap_top__DOT__pmem_write_TOP\n"); );
    // Body
    int waddr__Vcvt;
    waddr__Vcvt = waddr;
    int wdata__Vcvt;
    wdata__Vcvt = wdata;
    char wmask__Vcvt;
    wmask__Vcvt = wmask;
    pmem_write(waddr__Vcvt, wdata__Vcvt, wmask__Vcvt);
}

extern "C" void npc_ebreak(int pc);

void Vtop___024root____Vdpiimwrap_top__DOT__npc_ebreak_TOP(::IData/*31:0*/ pc) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root____Vdpiimwrap_top__DOT__npc_ebreak_TOP\n"); );
    // Body
    int pc__Vcvt;
    pc__Vcvt = pc;
    npc_ebreak(pc__Vcvt);
}

void Vtop___024root___eval_sample(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_sample\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(const ::VlUnpacked<::QData/*63:0*/, 2> &triggers, const ::std::string &tag);
#endif  // VL_DEBUG
bool Vtop___024root___trigger_anySet__ico(const ::VlUnpacked<::QData/*63:0*/, 2> &in);

bool Vtop___024root___eval_ico(Vtop___024root* vlSelf, ::CData/*0:0*/ firstIteration) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    ::CData/*0:0*/ __VicoExecute;
    // Body
    vlSelfRef.__VicoTriggered[1U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VicoTriggered[1U]) 
                                     | (::IData)((::IData)(firstIteration)));
    {
        // Body
        // Inlined CFunc: _eval_triggers_vec__ico
        vlSelfRef.__VicoTriggered[0U] = (::QData)((::IData)(
                                                            ((((::IData)(vlSelfRef.__VprimaryPorts.dbg_raddr) 
                                                               != (::IData)(vlSelfRef.__Vtrigprevexpr___TOP__dbg_raddr__0)) 
                                                              << 2U) 
                                                             | ((((::IData)(vlSelfRef.__VprimaryPorts.rst) 
                                                                  != (::IData)(vlSelfRef.__Vtrigprevexpr___TOP__rst__0)) 
                                                                 << 1U) 
                                                                | ((::IData)(vlSelfRef.__VprimaryPorts.clk) 
                                                                   != (::IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0))))));
        vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.__VprimaryPorts.clk;
        vlSelfRef.__Vtrigprevexpr___TOP__rst__0 = vlSelfRef.__VprimaryPorts.rst;
        vlSelfRef.__Vtrigprevexpr___TOP__dbg_raddr__0 
            = vlSelfRef.__VprimaryPorts.dbg_raddr;
    }
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtop___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
    __VicoExecute = Vtop___024root___trigger_anySet__ico(vlSelfRef.__VicoTriggered);
    if (__VicoExecute) {
        {
            // Body
            // Inlined CFunc: _eval_body__ico
            if ((((4ULL & vlSelfRef.__VicoTriggered[0U])) != 0ULL)) {
                {
                    // Body
                    // Inlined CFunc: _ico_comb__TOP__0
                    vlSelfRef.__VprimaryPorts.dbg_rdata 
                        = ((0U == (::IData)(vlSelfRef.__VprimaryPorts.dbg_raddr))
                            ? 0U : vlSelfRef.top__DOT__u_npc__DOT__u_regfile__DOT__rf
                           [vlSelfRef.__VprimaryPorts.dbg_raddr]);
                }
            }
        }
    }
    return (__VicoExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(const ::VlUnpacked<::QData/*63:0*/, 1> &triggers, const ::std::string &tag);
#endif  // VL_DEBUG
void Vtop___024root___trigger_orInto__act_vec_vec(::VlUnpacked<::QData/*63:0*/, 1> &out, const ::VlUnpacked<::QData/*63:0*/, 1> &in);

bool Vtop___024root___eval_act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    {
        // Body
        // Inlined CFunc: _eval_triggers_vec__act
        vlSelfRef.__VactTriggered[0U] = (::QData)((::IData)(
                                                            ((::IData)(vlSelfRef.__VprimaryPorts.clk) 
                                                             & (~ (::IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__1)))));
        vlSelfRef.__Vtrigprevexpr___TOP__clk__1 = vlSelfRef.__VprimaryPorts.clk;
    }
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtop___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vtop___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

bool Vtop___024root___eval_inact(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_inact\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    return (0U);
}

bool Vtop___024root___trigger_anySet__act(const ::VlUnpacked<::QData/*63:0*/, 1> &in);
void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf);
void Vtop___024root___trigger_clear__act(::VlUnpacked<::QData/*63:0*/, 1> &out);

bool Vtop___024root___eval_nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    ::CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtop___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        {
            // Body
            // Inlined CFunc: _eval_body__nba
            if ((((1ULL & vlSelfRef.__VnbaTriggered[0U])) != 0ULL)) {
                Vtop___024root___nba_sequent__TOP__0(vlSelf);
                vlSelfRef.__VtraceActivity[1U] = 1U;
            }
        }
        Vtop___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

bool Vtop___024root___eval_obs(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_obs\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    return (0U);
}

bool Vtop___024root___eval_react(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_react\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    return (0U);
}

void Vtop___024root___eval_postponed(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_postponed\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

bool Vtop___024root___trigger_anySet__ico(const ::VlUnpacked<::QData/*63:0*/, 2> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___trigger_anySet__ico\n"); );
    // Locals
    ::IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((::IData)(1U) + n);
    } while ((2U > n));
    return (0U);
}

bool Vtop___024root___trigger_anySet__act(const ::VlUnpacked<::QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___trigger_anySet__act\n"); );
    // Locals
    ::IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((::IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    ::IData/*31:0*/ __Vdly_Val__top__DOT__u_npc__DOT__u_regfile__DOT__rf_4;
    ::CData/*4:0*/ __Vdly_Dim0__top__DOT__u_npc__DOT__u_regfile__DOT__rf_5;
    ::CData/*0:0*/ __Vdly_Set__top__DOT__u_npc__DOT__u_regfile__DOT__rf_6;
    // Body
    __Vdly_Val__top__DOT__u_npc__DOT__u_regfile__DOT__rf_4 = 0;
    __Vdly_Dim0__top__DOT__u_npc__DOT__u_regfile__DOT__rf_5 = 0;
    __Vdly_Set__top__DOT__u_npc__DOT__u_regfile__DOT__rf_6 = 0;
    __Vdly_Set__top__DOT__u_npc__DOT__u_regfile__DOT__rf_6 = 0U;
    if (((::IData)(vlSelfRef.__VprimaryPorts.wen) & 
         (0U != (0x0000001fU & (vlSelfRef.top__DOT__ifu_rdata 
                                >> 7U))))) {
        __Vdly_Val__top__DOT__u_npc__DOT__u_regfile__DOT__rf_4 
            = ((0U == (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__wb_sel))
                ? vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__exudata
                : ((1U == (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__wb_sel))
                    ? (((::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__size)
                         ? vlSelfRef.top__DOT__lsu_rdata
                         : ((((- (::IData)((1U & ((::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_lsu__DOT__byte_data) 
                                                  >> 7U)))) 
                              & (- (::IData)((1U & 
                                              (~ (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__mem_unsigned)))))) 
                             << 8U) | (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_lsu__DOT__byte_data))) 
                       & (- (::IData)((::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__mem_read))))
                    : ((::IData)(4U) + vlSelfRef.top__DOT__u_npc__DOT__u_ifu__DOT__pc_reg)));
        __Vdly_Dim0__top__DOT__u_npc__DOT__u_regfile__DOT__rf_5 
            = (0x0000001fU & (vlSelfRef.top__DOT__ifu_rdata 
                              >> 7U));
        __Vdly_Set__top__DOT__u_npc__DOT__u_regfile__DOT__rf_6 = 1U;
    }
    if (__Vdly_Set__top__DOT__u_npc__DOT__u_regfile__DOT__rf_6) {
        vlSelfRef.top__DOT__u_npc__DOT__u_regfile__DOT__rf[__Vdly_Dim0__top__DOT__u_npc__DOT__u_regfile__DOT__rf_5] 
            = __Vdly_Val__top__DOT__u_npc__DOT__u_regfile__DOT__rf_4;
    }
    vlSelfRef.__VprimaryPorts.dbg_rdata = ((0U == (::IData)(vlSelfRef.__VprimaryPorts.dbg_raddr))
                                            ? 0U : vlSelfRef.top__DOT__u_npc__DOT__u_regfile__DOT__rf
                                           [vlSelfRef.__VprimaryPorts.dbg_raddr]);
    if (vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__mem_write) {
        vlSelfRef.top__DOT____VlemCond_1 = 0U;
    } else {
        Vtop___024root____Vdpiimwrap_top__DOT__pmem_read_TOP(vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__exudata, vlSelfRef.top__DOT____VlemCall_0__pmem_read);
        vlSelfRef.top__DOT____VlemCond_1 = vlSelfRef.top__DOT____VlemCall_0__pmem_read;
    }
    vlSelfRef.top__DOT__lsu_rdata = vlSelfRef.top__DOT____VlemCond_1;
    if (vlSelfRef.__VprimaryPorts.rst) {
        vlSelfRef.top__DOT____VlemCond_3 = 0U;
    } else {
        Vtop___024root____Vdpiimwrap_top__DOT__pmem_read_TOP(vlSelfRef.top__DOT__u_npc__DOT__u_ifu__DOT__pc_reg, vlSelfRef.top__DOT____VlemCall_2__pmem_read);
        vlSelfRef.top__DOT____VlemCond_3 = vlSelfRef.top__DOT____VlemCall_2__pmem_read;
    }
    vlSelfRef.top__DOT__ifu_rdata = vlSelfRef.top__DOT____VlemCond_3;
    if (((~ (::IData)(vlSelfRef.__VprimaryPorts.rst)) 
         & (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__mem_write))) {
        Vtop___024root____Vdpiimwrap_top__DOT__pmem_write_TOP(vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__exudata, 
                                                              ((::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__size)
                                                                ? vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__data2
                                                                : 
                                                               (vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__data2 
                                                                << 
                                                                (0x00000018U 
                                                                 & (vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__exudata 
                                                                    << 3U)))), 
                                                              ((::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__size)
                                                                ? 0x0000000fU
                                                                : 
                                                               (0x000000ffU 
                                                                & ((::IData)(1U) 
                                                                   << 
                                                                   (3U 
                                                                    & vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__exudata)))));
    }
    if (((~ (::IData)(vlSelfRef.__VprimaryPorts.rst)) 
         & (::IData)(vlSelfRef.__VprimaryPorts.is_ebreak))) {
        Vtop___024root____Vdpiimwrap_top__DOT__npc_ebreak_TOP(vlSelfRef.top__DOT__u_npc__DOT__u_ifu__DOT__pc_reg);
    }
    if (vlSelfRef.__VprimaryPorts.rst) {
        vlSelfRef.top__DOT__u_npc__DOT__u_ifu__DOT__pc_reg = 0x80000000U;
        vlSelfRef.top__DOT__u_npc__DOT__u_ifu__DOT__state = 0U;
    } else {
        if ((1U & (~ ((1U == (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_ifu__DOT__state)) 
                      & (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__mem_read))))) {
            if (((1U == (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_ifu__DOT__state)) 
                 & (~ (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__mem_read)))) {
                vlSelfRef.top__DOT__u_npc__DOT__u_ifu__DOT__pc_reg 
                    = vlSelfRef.__VprimaryPorts.npc;
            } else if ((2U == (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_ifu__DOT__state))) {
                vlSelfRef.top__DOT__u_npc__DOT__u_ifu__DOT__pc_reg 
                    = vlSelfRef.__VprimaryPorts.npc;
            }
        }
        vlSelfRef.top__DOT__u_npc__DOT__u_ifu__DOT__state 
            = vlSelfRef.__VprimaryPorts.next_state;
    }
    vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__data2 
        = ((0U == (0x0000001fU & (vlSelfRef.top__DOT__ifu_rdata 
                                  >> 0x00000014U)))
            ? 0U : vlSelfRef.top__DOT__u_npc__DOT__u_regfile__DOT__rf
           [(0x0000001fU & (vlSelfRef.top__DOT__ifu_rdata 
                            >> 0x00000014U))]);
    vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__is_add 
        = (::IData)((0x00000033U == (0xfe00707fU & vlSelfRef.top__DOT__ifu_rdata)));
    vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__is_sw 
        = (::IData)((0x00002023U == (0x0000707fU & vlSelfRef.top__DOT__ifu_rdata)));
    vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__data1 
        = ((0U == (0x0000001fU & (vlSelfRef.top__DOT__ifu_rdata 
                                  >> 0x0000000fU)))
            ? 0U : vlSelfRef.top__DOT__u_npc__DOT__u_regfile__DOT__rf
           [(0x0000001fU & (vlSelfRef.top__DOT__ifu_rdata 
                            >> 0x0000000fU))]);
    vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__mem_unsigned 
        = (::IData)((0x00004003U == (0x0000707fU & vlSelfRef.top__DOT__ifu_rdata)));
    vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__is_lw 
        = (::IData)((0x00002003U == (0x0000707fU & vlSelfRef.top__DOT__ifu_rdata)));
    vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__is_addi 
        = (::IData)((0x00000013U == (0x0000707fU & vlSelfRef.top__DOT__ifu_rdata)));
    vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__is_jalr 
        = (::IData)((0x00000067U == (0x0000707fU & vlSelfRef.top__DOT__ifu_rdata)));
    vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__S_type 
        = ((::IData)((0x00000023U == (0x0000707fU & vlSelfRef.top__DOT__ifu_rdata))) 
           | (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__is_sw));
    vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__size 
        = ((::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__is_lw) 
           | (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__is_sw));
    vlSelfRef.__Vdfg_Regularize_146 = ((::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__is_lw) 
                                       | (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__mem_unsigned));
    vlSelfRef.__Vdfg_Regularize_147 = ((::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__is_jalr) 
                                       | (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__is_addi));
    vlSelfRef.__VprimaryPorts.pc = vlSelfRef.top__DOT__u_npc__DOT__u_ifu__DOT__pc_reg;
    vlSelfRef.__Vdfg_Regularize_150 = ((::IData)(vlSelfRef.__Vdfg_Regularize_146) 
                                       | (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__S_type));
    vlSelfRef.__Vdfg_Regularize_151 = ((0x37U == (0x0000007fU 
                                                  & vlSelfRef.top__DOT__ifu_rdata)) 
                                       | (::IData)(vlSelfRef.__Vdfg_Regularize_147));
    vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__imm 
        = (((::IData)(vlSelfRef.__Vdfg_Regularize_147) 
            | (::IData)(vlSelfRef.__Vdfg_Regularize_146))
            ? (((- (::IData)((vlSelfRef.top__DOT__ifu_rdata 
                              >> 0x0000001fU))) << 0x0000000bU) 
               | (0x000007ffU & (vlSelfRef.top__DOT__ifu_rdata 
                                 >> 0x00000014U))) : 
           ((0x37U == (0x0000007fU & vlSelfRef.top__DOT__ifu_rdata))
             ? (0xfffff000U & vlSelfRef.top__DOT__ifu_rdata)
             : (((- (::IData)((vlSelfRef.top__DOT__ifu_rdata 
                               >> 0x0000001fU))) << 0x0000000bU) 
                | ((0x000007e0U & (vlSelfRef.top__DOT__ifu_rdata 
                                   >> 0x00000014U)) 
                   | (0x0000001fU & (vlSelfRef.top__DOT__ifu_rdata 
                                     >> 7U))))));
    vlSelfRef.__Vdfg_Regularize_149 = (vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__data1 
                                       + vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__imm);
    if (vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__is_jalr) {
        vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__wb_sel = 2U;
        vlSelfRef.__VprimaryPorts.npc = (0xfffffffeU 
                                         & vlSelfRef.__Vdfg_Regularize_149);
    } else {
        vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__wb_sel 
            = (1U & (- (::IData)((1U & (~ ((::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__is_addi) 
                                           | ((0x37U 
                                               == (0x0000007fU 
                                                   & vlSelfRef.top__DOT__ifu_rdata)) 
                                              | (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__is_add))))))));
        vlSelfRef.__VprimaryPorts.npc = ((::IData)(4U) 
                                         + vlSelfRef.top__DOT__u_npc__DOT__u_ifu__DOT__pc_reg);
    }
    vlSelfRef.__VprimaryPorts.inst_valid = ((1U == (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_ifu__DOT__state)) 
                                            | (2U == (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_ifu__DOT__state)));
    vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__exudata 
        = (((::IData)(vlSelfRef.__Vdfg_Regularize_151) 
            | (::IData)(vlSelfRef.__Vdfg_Regularize_150))
            ? ((0U == (1U & (- (::IData)(((::IData)(vlSelfRef.__Vdfg_Regularize_147) 
                                          | ((::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__is_add) 
                                             | (::IData)(vlSelfRef.__Vdfg_Regularize_150)))))))
                ? vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__imm
                : vlSelfRef.__Vdfg_Regularize_149) : 
           (vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__data1 
            + vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__data2));
    vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__mem_write 
        = ((::IData)(vlSelfRef.__VprimaryPorts.inst_valid) 
           & (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__S_type));
    vlSelfRef.__VprimaryPorts.is_ebreak = ((::IData)(vlSelfRef.__VprimaryPorts.inst_valid) 
                                           & (0x00100073U 
                                              == (0xfff0707fU 
                                                  & vlSelfRef.top__DOT__ifu_rdata)));
    vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__mem_read 
        = ((::IData)(vlSelfRef.__VprimaryPorts.inst_valid) 
           & (::IData)(vlSelfRef.__Vdfg_Regularize_146));
    vlSelfRef.top__DOT__u_npc__DOT__u_lsu__DOT__byte_data 
        = (0x000000ffU & (vlSelfRef.top__DOT__lsu_rdata 
                          >> (0x00000018U & (vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__exudata 
                                             << 3U))));
    vlSelfRef.__VprimaryPorts.next_state = ((0U == (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_ifu__DOT__state))
                                             ? 1U : 
                                            (2U & (- (::IData)(
                                                               ((1U 
                                                                 == (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_ifu__DOT__state)) 
                                                                & (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__mem_read))))));
    vlSelfRef.__VprimaryPorts.wen = ((::IData)(vlSelfRef.__VprimaryPorts.inst_valid) 
                                     & ((2U != (::IData)(vlSelfRef.__VprimaryPorts.next_state)) 
                                        & ((::IData)(vlSelfRef.__Vdfg_Regularize_151) 
                                           | ((::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__is_add) 
                                              | (::IData)(vlSelfRef.__Vdfg_Regularize_146)))));
}

void Vtop___024root___trigger_orInto__act_vec_vec(::VlUnpacked<::QData/*63:0*/, 1> &out, const ::VlUnpacked<::QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    ::IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((::IData)(1U) + n);
    } while ((0U >= n));
}

void Vtop___024root___trigger_clear__act(::VlUnpacked<::QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___trigger_clear__act\n"); );
    // Locals
    ::IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((::IData)(1U) + n);
    } while ((1U > n));
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.__VprimaryPorts.clk 
                      & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.__VprimaryPorts.rst 
                      & 0xfeU)))) {
        Verilated::overWidthError("rst");
    }
    if (VL_UNLIKELY(((vlSelfRef.__VprimaryPorts.dbg_raddr 
                      & 0xe0U)))) {
        Verilated::overWidthError("dbg_raddr");
    }
}
#endif  // VL_DEBUG
