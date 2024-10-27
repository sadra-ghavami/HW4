#ifndef BFM_MATRIX_MULT_TB_MACRO
#define BFM_MATRIX_MULT_TB_MACRO

#include <systemc.h>
#include "BFM_Matrix_Mult.h"
#include <iostream>

SC_MODULE(BFM_Matrix_Mult_TB1) {
	sc_signal<sc_logic>clk, rst, start, done;
	sc_signal<sc_lv<8>>D_matrix[3][3];
	sc_signal<sc_lv<8>>W_matrix[3][3];
	sc_signal<sc_lv<24>>result_matrix[3][3];
	BFM_Matrix_Mult<3,1>* BFM_test_multiplier;

	SC_CTOR(BFM_Matrix_Mult_TB1) {
		BFM_test_multiplier = new BFM_Matrix_Mult<3,1>("BFM_test");
		BFM_test_multiplier->clk(clk);
		BFM_test_multiplier->rst(rst);
		BFM_test_multiplier->start(start);
		BFM_test_multiplier->done(done);
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				BFM_test_multiplier->D_matrix[i][j](D_matrix[i][j]);
				BFM_test_multiplier->W_matrix[i][j](W_matrix[i][j]);
				BFM_test_multiplier->result_matrix[i][j](result_matrix[i][j]);
			}

		SC_THREAD(clk_generation);
		SC_THREAD(rst_generation);
		SC_THREAD(input_generation);

		SC_METHOD(print_result_when_ready);
		sensitive << done;
	}
	void clk_generation();
	void rst_generation();
	void input_generation();
	void print_result_when_ready();
};

#endif // !MATRIX_MULT_TB1_MACRO
