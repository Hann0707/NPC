// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


void Vtop___024root__trace_chg_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vtop___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_0\n"); );
    // Body
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    Vtop___024root__trace_chg_0_sub_0((&vlSymsp->vlInst.TOP), bufp);
}

void Vtop___024root__trace_chg_dtype____0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp, uint32_t offset, const ::VlUnpacked<::IData/*31:0*/, 32>& __VdtypeVar);

void Vtop___024root__trace_chg_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_0_sub_0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 0);
    if (VL_UNLIKELY((vlSelfRef.__VtraceActivity[1U]))) {
        bufp->chgIData(oldp+0,(vlSelfRef.top__DOT__u_npc__DOT__u_ifu__DOT__pc_reg),32);
        bufp->chgIData(oldp+1,(vlSelfRef.top__DOT__ifu_rdata),32);
        bufp->chgIData(oldp+2,(vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__exudata),32);
        bufp->chgIData(oldp+3,(((::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__size)
                                 ? vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__data2
                                 : (vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__data2 
                                    << (0x00000018U 
                                        & (vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__exudata 
                                           << 3U))))),32);
        bufp->chgCData(oldp+4,(((::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__size)
                                 ? 0x0000000fU : (0x000000ffU 
                                                  & ((::IData)(1U) 
                                                     << 
                                                     (3U 
                                                      & vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__exudata))))),8);
        bufp->chgBit(oldp+5,(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__mem_read));
        bufp->chgBit(oldp+6,(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__mem_write));
        bufp->chgIData(oldp+7,(vlSelfRef.top__DOT__lsu_rdata),32);
        bufp->chgCData(oldp+8,((0x0000001fU & (vlSelfRef.top__DOT__ifu_rdata 
                                               >> 7U))),5);
        bufp->chgCData(oldp+9,((0x0000001fU & (vlSelfRef.top__DOT__ifu_rdata 
                                               >> 0x0000000fU))),5);
        bufp->chgCData(oldp+10,((0x0000001fU & (vlSelfRef.top__DOT__ifu_rdata 
                                                >> 0x00000014U))),5);
        bufp->chgIData(oldp+11,(vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__data1),32);
        bufp->chgIData(oldp+12,(vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__data2),32);
        bufp->chgIData(oldp+13,(((0U == (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__wb_sel))
                                  ? vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__exudata
                                  : ((1U == (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__wb_sel))
                                      ? (((::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__size)
                                           ? vlSelfRef.top__DOT__lsu_rdata
                                           : ((((- (::IData)(
                                                             (1U 
                                                              & ((::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_lsu__DOT__byte_data) 
                                                                 >> 7U)))) 
                                                & (- (::IData)(
                                                               (1U 
                                                                & (~ (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__mem_unsigned)))))) 
                                               << 8U) 
                                              | (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_lsu__DOT__byte_data))) 
                                         & (- (::IData)((::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__mem_read))))
                                      : ((::IData)(4U) 
                                         + vlSelfRef.top__DOT__u_npc__DOT__u_ifu__DOT__pc_reg)))),32);
        bufp->chgIData(oldp+14,(vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__imm),32);
        bufp->chgBit(oldp+15,(vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__is_jalr));
        bufp->chgCData(oldp+16,((1U & (- (::IData)(
                                                   ((::IData)(vlSelfRef.__Vdfg_Regularize_147) 
                                                    | ((::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__is_add) 
                                                       | (::IData)(vlSelfRef.__Vdfg_Regularize_150))))))),2);
        bufp->chgBit(oldp+17,(((::IData)(vlSelfRef.__Vdfg_Regularize_151) 
                               | (::IData)(vlSelfRef.__Vdfg_Regularize_150))));
        bufp->chgIData(oldp+18,((((::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__size)
                                   ? vlSelfRef.top__DOT__lsu_rdata
                                   : ((((- (::IData)(
                                                     (1U 
                                                      & ((::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_lsu__DOT__byte_data) 
                                                         >> 7U)))) 
                                        & (- (::IData)(
                                                       (1U 
                                                        & (~ (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__mem_unsigned)))))) 
                                       << 8U) | (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_lsu__DOT__byte_data))) 
                                 & (- (::IData)((::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__mem_read))))),32);
        bufp->chgBit(oldp+19,(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__mem_unsigned));
        bufp->chgBit(oldp+20,(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__size));
        bufp->chgIData(oldp+21,((0xfffffffeU & vlSelfRef.__Vdfg_Regularize_149)),32);
        bufp->chgCData(oldp+22,(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__wb_sel),2);
        bufp->chgCData(oldp+23,((0x0000007fU & vlSelfRef.top__DOT__ifu_rdata)),7);
        bufp->chgCData(oldp+24,((7U & (vlSelfRef.top__DOT__ifu_rdata 
                                       >> 0x0000000cU))),3);
        bufp->chgBit(oldp+25,(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__is_addi));
        bufp->chgBit(oldp+26,((0x37U == (0x0000007fU 
                                         & vlSelfRef.top__DOT__ifu_rdata))));
        bufp->chgBit(oldp+27,(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__is_add));
        bufp->chgBit(oldp+28,(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__is_lw));
        bufp->chgBit(oldp+29,(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__is_sw));
        bufp->chgBit(oldp+30,((::IData)((0x00000023U 
                                         == (0x0000707fU 
                                             & vlSelfRef.top__DOT__ifu_rdata)))));
        bufp->chgIData(oldp+31,((((- (::IData)((vlSelfRef.top__DOT__ifu_rdata 
                                                >> 0x0000001fU))) 
                                  << 0x0000000bU) | 
                                 (0x000007ffU & (vlSelfRef.top__DOT__ifu_rdata 
                                                 >> 0x00000014U)))),32);
        bufp->chgIData(oldp+32,((0xfffff000U & vlSelfRef.top__DOT__ifu_rdata)),32);
        bufp->chgIData(oldp+33,((((- (::IData)((vlSelfRef.top__DOT__ifu_rdata 
                                                >> 0x0000001fU))) 
                                  << 0x0000000bU) | 
                                 ((0x000007e0U & (vlSelfRef.top__DOT__ifu_rdata 
                                                  >> 0x00000014U)) 
                                  | (0x0000001fU & 
                                     (vlSelfRef.top__DOT__ifu_rdata 
                                      >> 7U))))),32);
        bufp->chgBit(oldp+34,(((::IData)(vlSelfRef.__Vdfg_Regularize_147) 
                               | (::IData)(vlSelfRef.__Vdfg_Regularize_146))));
        bufp->chgBit(oldp+35,(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__S_type));
        bufp->chgCData(oldp+36,(vlSelfRef.top__DOT__u_npc__DOT__u_ifu__DOT__state),2);
        bufp->chgCData(oldp+37,((3U & vlSelfRef.top__DOT__u_npc__DOT__u_exu__DOT__exudata)),2);
        bufp->chgCData(oldp+38,(vlSelfRef.top__DOT__u_npc__DOT__u_lsu__DOT__byte_data),8);
        bufp->chgIData(oldp+39,(((::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__size)
                                  ? vlSelfRef.top__DOT__lsu_rdata
                                  : ((((- (::IData)(
                                                    (1U 
                                                     & ((::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_lsu__DOT__byte_data) 
                                                        >> 7U)))) 
                                       & (- (::IData)(
                                                      (1U 
                                                       & (~ (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_idu__DOT__mem_unsigned)))))) 
                                      << 8U) | (::IData)(vlSelfRef.top__DOT__u_npc__DOT__u_lsu__DOT__byte_data)))),32);
        Vtop___024root__trace_chg_dtype____0(vlSelf, bufp, 40, vlSelfRef.top__DOT__u_npc__DOT__u_regfile__DOT__rf);
    }
    bufp->chgBit(oldp+72,(vlSelfRef.__VprimaryPorts.clk));
    bufp->chgBit(oldp+73,(vlSelfRef.__VprimaryPorts.rst));
    bufp->chgIData(oldp+74,(vlSelfRef.__VprimaryPorts.npc),32);
    bufp->chgCData(oldp+75,(vlSelfRef.__VprimaryPorts.dbg_raddr),5);
    bufp->chgIData(oldp+76,(vlSelfRef.__VprimaryPorts.dbg_rdata),32);
    bufp->chgBit(oldp+77,(vlSelfRef.__VprimaryPorts.is_ebreak));
    bufp->chgBit(oldp+78,(vlSelfRef.__VprimaryPorts.inst_valid));
    bufp->chgBit(oldp+79,(vlSelfRef.__VprimaryPorts.wen));
    bufp->chgCData(oldp+80,(vlSelfRef.__VprimaryPorts.next_state),2);
}

void Vtop___024root__trace_chg_dtype____0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp, uint32_t offset, const ::VlUnpacked<::IData/*31:0*/, 32>& __VdtypeVar) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_dtype____0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode +  offset);
    bufp->chgIData(oldp+0,(__VdtypeVar[31]),32);
    bufp->chgIData(oldp+1,(__VdtypeVar[30]),32);
    bufp->chgIData(oldp+2,(__VdtypeVar[29]),32);
    bufp->chgIData(oldp+3,(__VdtypeVar[28]),32);
    bufp->chgIData(oldp+4,(__VdtypeVar[27]),32);
    bufp->chgIData(oldp+5,(__VdtypeVar[26]),32);
    bufp->chgIData(oldp+6,(__VdtypeVar[25]),32);
    bufp->chgIData(oldp+7,(__VdtypeVar[24]),32);
    bufp->chgIData(oldp+8,(__VdtypeVar[23]),32);
    bufp->chgIData(oldp+9,(__VdtypeVar[22]),32);
    bufp->chgIData(oldp+10,(__VdtypeVar[21]),32);
    bufp->chgIData(oldp+11,(__VdtypeVar[20]),32);
    bufp->chgIData(oldp+12,(__VdtypeVar[19]),32);
    bufp->chgIData(oldp+13,(__VdtypeVar[18]),32);
    bufp->chgIData(oldp+14,(__VdtypeVar[17]),32);
    bufp->chgIData(oldp+15,(__VdtypeVar[16]),32);
    bufp->chgIData(oldp+16,(__VdtypeVar[15]),32);
    bufp->chgIData(oldp+17,(__VdtypeVar[14]),32);
    bufp->chgIData(oldp+18,(__VdtypeVar[13]),32);
    bufp->chgIData(oldp+19,(__VdtypeVar[12]),32);
    bufp->chgIData(oldp+20,(__VdtypeVar[11]),32);
    bufp->chgIData(oldp+21,(__VdtypeVar[10]),32);
    bufp->chgIData(oldp+22,(__VdtypeVar[9]),32);
    bufp->chgIData(oldp+23,(__VdtypeVar[8]),32);
    bufp->chgIData(oldp+24,(__VdtypeVar[7]),32);
    bufp->chgIData(oldp+25,(__VdtypeVar[6]),32);
    bufp->chgIData(oldp+26,(__VdtypeVar[5]),32);
    bufp->chgIData(oldp+27,(__VdtypeVar[4]),32);
    bufp->chgIData(oldp+28,(__VdtypeVar[3]),32);
    bufp->chgIData(oldp+29,(__VdtypeVar[2]),32);
    bufp->chgIData(oldp+30,(__VdtypeVar[1]),32);
    bufp->chgIData(oldp+31,(__VdtypeVar[0]),32);
}

void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_cleanup\n"); );
    // Body
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSymsp->__Vm_activity = false;
    vlSymsp->vlInst.TOP.__VtraceActivity[0U] = 0U;
    vlSymsp->vlInst.TOP.__VtraceActivity[1U] = 0U;
}
