.DEFAULT_GOAL := sim

VSRC := $(filter-out vsrc/top.v vsrc/ysyx_100025070.v,$(wildcard vsrc/*.v))
VSRC += $(shell find ../ysyxSoC/perip -type f \( -name '*.v' -o -name '*.sv' \))
CSRC := csrc/main.cpp
INC_DIRS := -I../ysyxSoC/perip/uart16550/rtl \
            -I../ysyxSoC/perip/spi/rtl
RANDOM_DELAY ?= 0

# NVBoard 的约束文件和自动生成的引脚绑定代码
NXDC_FILE := constr/SimTop.nxdc
AUTO_BIND := $(abspath build/auto_bind.cpp)

include $(NVBOARD_HOME)/scripts/nvboard.mk

$(AUTO_BIND): $(NXDC_FILE)
	mkdir -p build
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $(NXDC_FILE) $(AUTO_BIND)

sim: $(AUTO_BIND) $(NVBOARD_ARCHIVE)
	verilator --cc --exe --build -j 0 -Wall -Wno-fatal \
	  --top-module SimTop --timescale "1ns/1ns" --no-timing \
	  -D__VERILOG__ -DPDK_BEHAV -D__UART_TO_CONSOLE__ -DNPC_RANDOM_DELAY=$(RANDOM_DELAY) \
	  $(INC_DIRS) ../ysyxSoC/ready-to-run/minirv/ElaborateTop.v $(VSRC) $(CSRC) $(AUTO_BIND) $(NVBOARD_ARCHIVE) \
	  -CFLAGS "-I$(NVBOARD_USR_INC)" -LDFLAGS "$(LDFLAGS)" -o sim

run: sim
	./obj_dir/sim $(ARGS)

clean:
	rm -rf obj_dir build

.PHONY: sim run clean
