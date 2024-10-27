#include "shift_reg_test.h"

void shift_reg_test::clkgeneration() {
	while (true) {
		clock = SC_LOGIC_0;
		wait(10, SC_NS);
		clock = SC_LOGIC_1;
		wait(10, SC_NS);
	}
}

void shift_reg_test::resetgn() {
	reset = SC_LOGIC_0;
	wait(2, SC_NS);
	reset = SC_LOGIC_1;
	wait(5, SC_NS);
	reset = SC_LOGIC_0;
}

void shift_reg_test::inputgen() {
	input_bus = "00000000";
	parallel_in[0] = "11111110";
	parallel_in[1] = "11111101";
	parallel_in[2] = "11111011";
	parallel_in[3] = "11110111";
	wait(20, SC_NS);
	load_register = SC_LOGIC_1;
	wait(20, SC_NS);
	load_register = SC_LOGIC_0;
	shift_enable = SC_LOGIC_1;
	wait(100, SC_NS);
}