#ifndef SHIFT_REG_MACRO
#define SHIFT_REG_MACRO

#include <systemc.h>

template<int reg_size, int bit_num>
SC_MODULE(shift_reg) {
	sc_in<sc_logic>clk, rst, shift_en, load_reg;
	sc_in<sc_lv<bit_num>> input;

	sc_in<sc_lv<bit_num>> par_in[reg_size];
	sc_out<sc_lv<bit_num>> par_out[reg_size];

	SC_CTOR(shift_reg) {
		SC_METHOD(shifting);
		sensitive << clk << rst;
	}
	void shifting();
};

template<int reg_size, int bit_num>
void shift_reg<reg_size, bit_num>::shifting() {
	if (rst == SC_LOGIC_1)
		for (int i = 0; i < reg_size; i++)
			par_out[i] = 0;
	else if (clk->event() && clk == SC_LOGIC_1) {
		if (load_reg == SC_LOGIC_1)
			for (int i = 0; i < reg_size; i++)
				par_out[i] = par_in[i];
		else if (shift_en == SC_LOGIC_1) {
			for (int i = 1; i < reg_size; i++) {
				par_out[i] = par_out[i - 1];
			}
			par_out[0] = input;
		}
	}
}

#endif // !SHIFT_REG_MACRO
