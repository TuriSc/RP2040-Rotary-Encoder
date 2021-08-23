TCL = $(shell dirname $(shell realpath $(shell which openocd)))/../tcl

.PHONY:
run: build
	openocd -s ${TCL} -f interface/picoprobe.cfg -f target/rp2040.cfg -c "program $(wildcard build/*.elf) verify reset exit"

build: *.c build/deps
	cd build && cmake .. && make -j8

build/deps: clib.json
	clib install -do build/deps
