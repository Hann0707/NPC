sim:
    verilator --cc --exe --build -j 0 -Wall -Wno-fatal \
    vsrc/NPC.v vsrc/IFU.v vsrc/IDU.v vsrc/EXU.v vsrc/WBU.v vsrc/regfile.v \
    csrc/main.cpp --top-module top -o sim
    ./obj_dir/sim
