#ifndef MATRIX_MULT_TB1_MACRO
#define MATRIX_MULT_TB1_MACRO

#include <systemc.h>
#include "Matrix_Mult.h"
#include <iostream>

SC_MODULE(Matrix_Mult_TB1) {
	sc_signal<sc_logic>clk, rst, start, done;
	sc_signal<sc_lv<8>>D_matrix[3][3];
	sc_signal<sc_lv<8>>W_matrix[3][3];
	sc_signal<sc_lv<24>>result_matrix[3][3];
	Matrix_Mult<3,1>* test_multiplier;

	SC_CTOR(Matrix_Mult_TB1) {
		test_multiplier = new Matrix_Mult<3,1>("new_test");
		test_multiplier->clk(clk);
		test_multiplier->rst(rst);
		test_multiplier->start(start);
		test_multiplier->done(done);
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				test_multiplier->D_matrix[i][j](D_matrix[i][j]);
				test_multiplier->W_matrix[i][j](W_matrix[i][j]);
				test_multiplier->result_matrix[i][j](result_matrix[i][j]);
			}

		SC_THREAD(clk_generation);
		SC_THREAD(rst_generation);
		SC_THREAD(input_generation);

		SC_METHOD(print_output_when_ready);
		sensitive << done;
	}
	void clk_generation();
	void rst_generation();
	void input_generation();
	void print_output_when_ready();
};



#endif // !MATRIX_MULT_TB1_MACRO