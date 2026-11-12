// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"

void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf);

void Vtop___024root__ctor(Vtop___024root* vlSelf, Vtop__Syms* symsp, const char* namep) {
    vlSelf->vlSymsp = symsp;
    vlSelf->vlNamep = strdup(namep);
    // Construct members
    // Reset structure values
    Vtop___024root___ctor_var_reset(vlSelf);
}

Vtop___024root::Vtop___024root(Vtop__Syms* symsp, const char* namep) {
    Vtop___024root__ctor(this, symsp, namep);
}

void Vtop___024root__dtor(Vtop___024root* vlSelf) {
    // Destroy members
    VL_DO_DANGLING(std::free(const_cast<char*>(vlSelf->vlNamep)), vlSelf->vlNamep);
}

Vtop___024root::~Vtop___024root() {
    Vtop___024root__dtor(this);
}
