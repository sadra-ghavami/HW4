#ifndef MATRIX_MULT_MACRO
#define MATRIX_MULT_MACRO

#include <systemc.h>
#include "Matrix_Mult_Datapath.h"
#include "Matrix_Mult_Controller.h"
#include <iostream>

template<int matrix_size, int iteration_num>
SC_MODULE(Matrix_Mult) {
	sc_in<sc_logic>clk, rst, start;
	sc_out<sc_logic>done;
	sc_signal<sc_logic>D_reg_load[matrix_size];
	sc_signal<sc_logic>D_reg_shift_en[matrix_size];
	sc_signal<sc_logic>R_reg_load[matrix_size];
	sc_signal<sc_logic>R_reg_shift_en[matrix_size];
	sc_signal<sc_logic>W_reg_load[matrix_size];
	sc_signal<sc_logic>W_reg_shift_en[matrix_size];
	sc_signal<sc_logic>start_PE_signals[matrix_size][matrix_size];
	sc_signal<sc_logic>busy_PE_signals[matrix_size][matrix_size];
	sc_in< sc_lv<8> > W_matrix[matrix_size][matrix_size];
	sc_in< sc_lv<8> > D_matrix[matrix_size][matrix_size];
	sc_out< sc_lv<24> > result_matrix[matrix_size][matrix_size];

	Matrix_Mult_Datapath<matrix_size>* datapath;
	Matrix_Mult_Controller<matrix_size,iteration_num>* controller;

	SC_CTOR(Matrix_Mult) {
		datapath = new Matrix_Mult_Datapath<matrix_size>("dt_path");
		datapath->clk(clk);
		datapath->rst(rst);
		for (int i = 0; i < matrix_size; i++) {
			datapath->D_reg_load[i](D_reg_load[i]);
			datapath->D_reg_shift_en[i](D_reg_shift_en[i]);
			datapath->W_reg_load[i](W_reg_load[i]);
			datapath->W_reg_shift_en[i](W_reg_shift_en[i]);
			datapath->R_reg_load[i](R_reg_load[i]);
			datapath->R_reg_shift_en[i](R_reg_shift_en[i]);
			for (int j = 0; j < matrix_size; j++) {
				datapath->D_matrix[i][j](D_matrix[i][j]);
				datapath->W_matrix[i][j](W_matrix[i][j]);
				datapath->result_matrix[i][j](result_matrix[i][j]);
				datapath->start_PE_signals[i][j](start_PE_signals[i][j]);
				datapath->busy_PE_signals[i][j](busy_PE_signals[i][j]);
			}
		}

		controller = new Matrix_Mult_Controller<matrix_size,iteration_num>("controller");
		controller->clk(clk);
		controller->rst(rst);
		controller->start(start);
		controller->done(done);
		for (int i = 0; i < matrix_size; i++) {
			controller->D_reg_load[i](D_reg_load[i]);
			controller->D_reg_shift_en[i](D_reg_shift_en[i]);
			controller->W_reg_load[i](W_reg_load[i]);
			controller->W_reg_shift_en[i](W_reg_shift_en[i]);
			controller->R_reg_load[i](R_reg_load[i]);
			controller->R_reg_shift_en[i](R_reg_shift_en[i]);
			for (int j = 0; j < matrix_size; j++) {
				controller->start_PE_signals[i][j](start_PE_signals[i][j]);
				controller->busy_PE_signals[i][j](busy_PE_signals[i][j]);
			}
		}

	}
};

#endif // !MATRIX_MULT_MACRO