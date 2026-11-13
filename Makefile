VSRC := $(wildcard vsrc/*.v)
CSRC := $(wildcard csrc/*.cpp)
RANDOM_DELAY ?= 0

sim:
	verilator --cc --exe --build -j 0 -Wall -Wno-fatal \
	  --top-module top -GRANDOM_DELAY=$(RANDOM_DELAY) $(VSRC) $(CSRC) -o sim
	./obj_dir/sim

clean:
	rm -rf obj_dir

