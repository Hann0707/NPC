// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"

VL_ATTR_COLD void Vtop___024root___eval_static(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_static\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.__VprimaryPorts.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst__0 = vlSelfRef.__VprimaryPorts.rst;
    vlSelfRef.__Vtrigprevexpr___TOP__dbg_raddr__0 = vlSelfRef.__VprimaryPorts.dbg_raddr;
    vlSelfRef.__Vtrigprevexpr___TOP__clk__1 = vlSelfRef.__VprimaryPorts.clk;
}

VL_ATTR_COLD void Vtop___024root___eval_initial(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(const ::VlUnpacked<::QData/*63:0*/, 1> &triggers, const ::std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtop___024root___trigger_anySet__stl(const ::VlUnpacked<::QData/*63:0*/, 1> &in);
VL_ATTR_COLD void Vtop___024root___stl_comb__TOP__0(Vtop___024root* vlSelf);

VL_ATTR_COLD bool Vtop___024root___eval_stl(Vtop___024root* vlSelf, ::CData/*0:0*/ firstIteration) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    ::CData/*0:0*/ __VstlExecute;
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (::IData)((::IData)(firstIteration)));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtop___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vtop___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        {
            // Body
            // Inlined CFunc: _eval_body__stl
            if ((((1ULL & vlSelfRef.__VstlTriggered[0U])) != 0ULL)) {
                Vtop___024root___stl_comb__TOP__0(vlSelf);
                {
                    // Body
                    // Inlined CFunc: __VtraceActivitySetAll
                    vlSelfRef.__VtraceActivity[0U] = 1U;
                    vlSelfRef.__VtraceActivity[1U] = 1U;
                }
            }
        }
    }
    return (__VstlExecute);
}

VL_ATTR_COLD void Vtop___024root___eval_dump_triggers__stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_dump_triggers__stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
#ifdef VL_DEBUG
    Vtop___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(const ::VlUnpacked<::QData/*63:0*/, 2> &triggers, const ::std::string &tag);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop___024root___eval_dump_triggers__ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_dump_triggers__ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
#ifdef VL_DEBUG
    Vtop___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(const ::VlUnpacked<::QData/*63:0*/, 1> &triggers, const ::std::string &tag);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop___024root___eval_dump_triggers__act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_dump_triggers__act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
#ifdef VL_DEBUG
    Vtop___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
}

VL_ATTR_COLD void Vtop___024root___eval_dump_triggers__nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_dump_triggers__nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
#ifdef VL_DEBUG
    Vtop___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
}

VL_ATTR_COLD void Vtop___024root___eval_dump_triggers__obs(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_dump_triggers__obs\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vtop___024root___eval_dump_triggers__react(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_dump_triggers__react\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vtop___024root___eval_final(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_final\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(const ::VlUnpacked<::QData/*63:0*/, 1> &triggers, const ::std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (::IData)(Vtop___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (::IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vtop___024root___trigger_anySet__stl(const ::VlUnpacked<::QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void Vtop___024root___stl_comb__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___stl_comb__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VprimaryPorts.pc = vlSelfRef.top__DOT__u_npc__DOT__u_ifu__DOT__pc_reg;
    vlSelfRef.__VprimaryPorts.dbg_rdata = ((0U == (::IData)(vlSelfRef.__VprimaryPorts.dbg_raddr))
                                            ? 0U : vlSelfRef.top__DOT__u_npc__DOT__u_regfile__DOT__rf
                                           [vlSelfRef.__VprimaryPorts.dbg_raddr]);
    vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__data2 
        = ((0U == (0x0000001fU & (vlSelfRef.top__DOT__ifu_rdata 
                                  >> 0x00000014U)))
            ? 0U : vlSelfRef.top__DOT__u_npc__DOT__u_regfile__DOT__rf
           [(0x0000001fU & (vlSelfRef.top__DOT__ifu_rdata 
                            >> 0x00000014U))]);
    vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__is_add 
        = (::IData)((0x00000033U == (0xfe00707fU & vlSelfRef.top__DOT__ifu_rdata)));
    vlSelfRef.__VprimaryPorts.inst_valid = ((1U == (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_ifu__DOT__state)) 
                                            | (2U == (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_ifu__DOT__state)));
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
    vlSelfRef.__VprimaryPorts.is_ebreak = ((::IData)(vlSelfRef.__VprimaryPorts.inst_valid) 
                                           & (0x00100073U 
                                              == (0xfff0707fU 
                                                  & vlSelfRef.top__DOT__ifu_rdata)));
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
    vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__mem_write 
        = ((::IData)(vlSelfRef.__VprimaryPorts.inst_valid) 
           & (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__S_type));
    vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__mem_read 
        = ((::IData)(vlSelfRef.__VprimaryPorts.inst_valid) 
           & (::IData)(vlSelfRef.__Vdfg_Regularize_146));
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
    vlSelfRef.__VprimaryPorts.next_state = ((0U == (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_ifu__DOT__state))
                                             ? 1U : 
                                            (2U & (- (::IData)(
                                                               ((1U 
                                                                 == (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_ifu__DOT__state)) 
                                                                & (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__mem_read))))));
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
    vlSelfRef.__VprimaryPorts.wen = ((::IData)(vlSelfRef.__VprimaryPorts.inst_valid) 
                                     & ((2U != (::IData)(vlSelfRef.__VprimaryPorts.next_state)) 
                                        & ((::IData)(vlSelfRef.__Vdfg_Regularize_151) 
                                           | ((::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__is_add) 
                                              | (::IData)(vlSelfRef.__Vdfg_Regularize_146)))));
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
    vlSelfRef.top__DOT__u_npc__DOT__u_lsu__DOT__byte_data 
        = (0x000000ffU & (vlSelfRef.top__DOT__lsu_rdata 
                          >> (0x00000018U & (vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__exudata 
                                             << 3U))));
}

bool Vtop___024root___trigger_anySet__ico(const ::VlUnpacked<::QData/*63:0*/, 2> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(const ::VlUnpacked<::QData/*63:0*/, 2> &triggers, const ::std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (::IData)(Vtop___024root___trigger_anySet__ico(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (::IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @( clk)\n");
    }
    if ((1U & (::IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @( rst)\n");
    }
    if ((1U & (::IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @( dbg_raddr)\n");
    }
    if ((1U & (::IData)(triggers[1U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 64 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

bool Vtop___024root___trigger_anySet__act(const ::VlUnpacked<::QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(const ::VlUnpacked<::QData/*63:0*/, 1> &triggers, const ::std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (::IData)(Vtop___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (::IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ctor_var_reset\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->__VprimaryPorts.clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->__VprimaryPorts.rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18209466448985614591ull);
    vlSelf->__VprimaryPorts.npc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2449365538687681195ull);
    vlSelf->__VprimaryPorts.pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4211327832146562899ull);
    vlSelf->__VprimaryPorts.dbg_raddr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 3464027489234601205ull);
    vlSelf->__VprimaryPorts.dbg_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8642705063052842340ull);
    vlSelf->__VprimaryPorts.is_ebreak = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17481212467687349763ull);
    vlSelf->__VprimaryPorts.inst_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2881661861247159430ull);
    vlSelf->__VprimaryPorts.wen = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12409248811792671830ull);
    vlSelf->__VprimaryPorts.next_state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 10383377256973303270ull);
    vlSelf->top__DOT__ifu_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2772403880220773911ull);
    vlSelf->top__DOT__lsu_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5717850918461618104ull);
    vlSelf->top__DOT__u_npc__DOT__mem_read = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9645728201075622745ull);
    vlSelf->top__DOT__u_npc__DOT__u_lsu__DOT__byte_data = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 2771734956605798138ull);
    vlSelf->top__DOT__u_npc__DOT__u_regfile__DOT__rf[0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11255188008057887900ull);
    VL_UNPACKED_FILL(vlSelf->top__DOT__u_npc__DOT__u_regfile__DOT__rf.data(), sizeof(vlSelf->top__DOT__u_npc__DOT__u_regfile__DOT__rf[0]), 32);
    vlSelf->top__DOT__u_npc__DOT__u_exu__DOT__is_jalr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2210686659055835666ull);
    vlSelf->top__DOT__u_npc__DOT__u_exu__DOT__data1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7809593953075805441ull);
    vlSelf->top__DOT__u_npc__DOT__u_exu__DOT__data2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7065439538534278917ull);
    vlSelf->top__DOT__u_npc__DOT__u_exu__DOT__imm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2606396084331285889ull);
    vlSelf->top__DOT__u_npc__DOT__u_exu__DOT__exudata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1688477353133644459ull);
    vlSelf->top__DOT__u_npc__DOT__u_ifu__DOT__pc_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13324525584316056224ull);
    vlSelf->top__DOT__u_npc__DOT__u_ifu__DOT__state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 11648562593194935258ull);
    vlSelf->top__DOT__u_npc__DOT__u_idu__DOT__mem_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17603882767093565456ull);
    vlSelf->top__DOT__u_npc__DOT__u_idu__DOT__mem_read = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5974842567105261191ull);
    vlSelf->top__DOT__u_npc__DOT__u_idu__DOT__mem_unsigned = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11446271857870319225ull);
    vlSelf->top__DOT__u_npc__DOT__u_idu__DOT__size = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2907082872932663273ull);
    vlSelf->top__DOT__u_npc__DOT__u_idu__DOT__wb_sel = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 1271002894317231274ull);
    vlSelf->top__DOT__u_npc__DOT__u_idu__DOT__is_addi = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14951537416330042668ull);
    vlSelf->top__DOT__u_npc__DOT__u_idu__DOT__is_add = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11411741542554707678ull);
    vlSelf->top__DOT__u_npc__DOT__u_idu__DOT__is_lw = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15671316923311447893ull);
    vlSelf->top__DOT__u_npc__DOT__u_idu__DOT__is_sw = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7218482087865634178ull);
    vlSelf->top__DOT__u_npc__DOT__u_idu__DOT__S_type = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4512167028892134138ull);
    vlSelf->__Vdfg_Regularize_146 = 0;
    vlSelf->__Vdfg_Regularize_147 = 0;
    vlSelf->__Vdfg_Regularize_149 = 0;
    vlSelf->__Vdfg_Regularize_150 = 0;
    vlSelf->__Vdfg_Regularize_151 = 0;
    vlSelf->__VstlTriggered[0] = 0;
    VL_UNPACKED_FILL(vlSelf->__VstlTriggered.data(), sizeof(vlSelf->__VstlTriggered[0]), 1);
    vlSelf->__VicoTriggered[0] = 0;
    VL_UNPACKED_FILL(vlSelf->__VicoTriggered.data(), sizeof(vlSelf->__VicoTriggered[0]), 2);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__rst__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__dbg_raddr__0 = 0;
    vlSelf->__VactTriggered[0] = 0;
    VL_UNPACKED_FILL(vlSelf->__VactTriggered.data(), sizeof(vlSelf->__VactTriggered[0]), 1);
    vlSelf->__Vtrigprevexpr___TOP__clk__1 = 0;
    vlSelf->__VnbaTriggered[0] = 0;
    VL_UNPACKED_FILL(vlSelf->__VnbaTriggered.data(), sizeof(vlSelf->__VnbaTriggered[0]), 1);
    vlSelf->__VtraceActivity[0] = 0;
    VL_UNPACKED_FILL(vlSelf->__VtraceActivity.data(), sizeof(vlSelf->__VtraceActivity[0]), 2);
}
