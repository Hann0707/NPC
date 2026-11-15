VSRC := $(filter-out vsrc/top.v vsrc/ysyx_100025070.v,$(wildcard vsrc/*.v))
VSRC += $(shell find ../ysyxSoC/perip -type f \( -name '*.v' -o -name '*.sv' \))

CSRC := csrc/main.cpp
INC_DIRS := -I../ysyxSoC/perip/uart16550/rtl \
            -I../ysyxSoC/perip/spi/rtl

RANDOM_DELAY ?= 0

sim:
	verilator --cc --exe --build -j 0 -Wall -Wno-fatal \
	--top-module SimTop --timescale "1ns/1ns" --no-timing \
	-D__VERILOG__ -DPDK_BEHAV -D__UART_TO_CONSOLE__ -DNPC_RANDOM_DELAY=$(RANDOM_DELAY) \
	$(INC_DIRS) ../ysyxSoC/ready-to-run/minirv/ElaborateTop.v $(VSRC) $(CSRC) -o sim
	

clean:
	rm -rf obj_dir

