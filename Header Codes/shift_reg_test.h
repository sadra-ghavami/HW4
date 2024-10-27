#ifndef SHIFT_REG_TEST_MACRO
#define SHIFT_REG_TEST_MACRO

#include "shift_reg.h"

SC_MODULE(shift_reg_test) {
	sc_signal<sc_logic>clock, reset, shift_enable, load_register;
	sc_signal<sc_lv<8>> input_bus;
	
	sc_signal<sc_lv<8>> parallel_in[4];
	sc_signal<sc_lv<8>> parallel_out[4];

	shift_reg<4,8>* test_reg;

	SC_CTOR(shift_reg_test) {
		test_reg = new shift_reg<4,8>("reg_instance");
		test_reg->clk(clock);
		test_reg->rst(reset);
		test_reg->shift_en(shift_enable);
		test_reg->load_reg(load_register);
		test_reg->input(input_bus);
		test_reg->par_in[0](parallel_in[0]);
		test_reg->par_in[1](parallel_in[1]);
		test_reg->par_in[2](parallel_in[2]);
		test_reg->par_in[3](parallel_in[3]);
		test_reg->par_out[0](parallel_out[0]);
		test_reg->par_out[1](parallel_out[1]);
		test_reg->par_out[2](parallel_out[2]);
		test_reg->par_out[3](parallel_out[3]);
		SC_THREAD(clkgeneration);
		SC_THREAD(resetgn);
		SC_THREAD(inputgen);
	}
	void clkgeneration();
	void resetgn();
	void inputgen();
};

#endif // !SHIFT_REG_TEST_MACRO

