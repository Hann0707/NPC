VSRC := $(wildcard vsrc/*.v)
CSRC := $(wildcard csrc/*.cpp)

sim:
	verilator --cc --exe --build -j 0 -Wall -Wno-fatal \
	  --top-module top $(VSRC) $(CSRC) -o sim
	./obj_dir/sim

clean:
	rm -rf obj_dir

