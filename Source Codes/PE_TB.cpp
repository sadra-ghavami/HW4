#include "PE_TB.h"

void PE_TB::clk_generating() {
	while (true) {
		clock = SC_LOGIC_0;
		wait(10, SC_NS);
		clock = SC_LOGIC_1;
		wait(10, SC_NS);
	}
}

void PE_TB::reset_assertion() {
	reset = SC_LOGIC_0;
	wait(2, SC_NS);
	reset = SC_LOGIC_1;
	wait(5, SC_NS);
	reset = SC_LOGIC_0;
}

void PE_TB::input_generating() {
	start = SC_LOGIC_0;
	busy_PE = SC_LOGIC_0;
	Sin = "000000000000000000000000";
	wait(42, SC_NS);
	Win = "00000010";
	start = SC_LOGIC_1;
	wait(20, SC_NS);
	Win = "00000100";
	wait(20, SC_NS);
	start = SC_LOGIC_0;
	Din = "00000010";
	wait(40, SC_NS);
	busy_PE = SC_LOGIC_1;
	Din = "00001000";
	wait(20, SC_NS);
	Din = "00010000";
	Sin = "000000000000000000000010";
	wait(20, SC_NS);
	Din = "00000011";
	Sin = "000000000000000000000111";
	wait(20, SC_NS);
	busy_PE = SC_LOGIC_0;
	wait(400, SC_NS);
}