#ifndef MATRIX_MULT_CONTROLLER_MACRO
#define MATRIX_MULT_CONTROLLER_MACRO

#include <systemc.h>

template<int mult_size, int iteration_num>
SC_MODULE(Matrix_Mult_Controller) {
	sc_in<sc_logic>clk, rst, start;
	sc_out<sc_logic>done;
	sc_out<sc_logic>D_reg_load[mult_size];
	sc_out<sc_logic>D_reg_shift_en[mult_size];
	sc_out<sc_logic>R_reg_load[mult_size];
	sc_out<sc_logic>R_reg_shift_en[mult_size];
	sc_out<sc_logic>W_reg_load[mult_size];
	sc_out<sc_logic>W_reg_shift_en[mult_size];
	sc_out<sc_logic>start_PE_signals[mult_size][mult_size];
	sc_out<sc_logic>busy_PE_signals[mult_size][mult_size];

	enum states{S0,S1,S2,S3,S4,S5};
	sc_signal<states> Pstate,Nstate;

	sc_signal<sc_lv<2*mult_size>>count;
	sc_signal<sc_logic>init_count;
	sc_signal<sc_logic>inc_count;

	sc_signal<sc_lv<2 * iteration_num>>iteration_cnt;
	sc_signal<sc_logic>init_iteration_cnt;
	sc_signal<sc_logic>inc_iteration_cnt;

	SC_CTOR(Matrix_Mult_Controller) {
		Pstate = S0;
		Nstate = S0;
		count = 0;
		iteration_cnt = 0;
		SC_METHOD(counting);
			sensitive << clk << rst;

		SC_METHOD(iteration_counting);
			sensitive << clk << rst;

		SC_METHOD(comb_part);
			sensitive << start << Pstate << count;

		SC_METHOD(seq_part);
			sensitive << clk << rst;
	}

	void counting();
	void iteration_counting();
	void comb_part();
	void seq_part();
};

template<int mult_size, int iteration_num>
void Matrix_Mult_Controller<mult_size, iteration_num>::counting() {
	if (rst == SC_LOGIC_1)
		count = 0;
	else if (clk->event() && clk == SC_LOGIC_1) {
		if (init_count == SC_LOGIC_1)
			count = 0;
		else if (inc_count == SC_LOGIC_1)
			count = count.read().to_uint() + 1;
	}
}

template<int mult_size, int iteration_num>
void Matrix_Mult_Controller<mult_size, iteration_num>::iteration_counting() {
	if (rst == SC_LOGIC_1)
		iteration_cnt = 0;
	else if (clk->event() && clk == SC_LOGIC_1) {
		if (init_iteration_cnt == SC_LOGIC_1)
			iteration_cnt = 0;
		else if (inc_iteration_cnt == SC_LOGIC_1)
			iteration_cnt = iteration_cnt.read().to_uint() + 1;
	}
}

template<int mult_size, int iteration_num>
void Matrix_Mult_Controller<mult_size, iteration_num>::seq_part() {
	if (rst == SC_LOGIC_1) {
		Pstate = S0;
		//Nstate = S0;
	}
	else if (clk->event() && clk == SC_LOGIC_1) {
		Pstate = Nstate;
	}
}

template<int mult_size, int iteration_num>
void Matrix_Mult_Controller<mult_size, iteration_num>::comb_part() {
	inc_count.write(SC_LOGIC_0);
	init_count.write(SC_LOGIC_0);
	init_iteration_cnt.write(SC_LOGIC_0);
	inc_iteration_cnt.write(SC_LOGIC_0);
	done->write(SC_LOGIC_0);
	for (int i = 0; i < mult_size; i++) {
		D_reg_load[i]->write(SC_LOGIC_0);
		D_reg_shift_en[i]->write(SC_LOGIC_0);
		W_reg_load[i]->write(SC_LOGIC_0);
		W_reg_shift_en[i]->write(SC_LOGIC_0);
		R_reg_load[i]->write(SC_LOGIC_0);
		R_reg_shift_en[i]->write(SC_LOGIC_0);
		for (int j = 0; j < mult_size; j++) {
			start_PE_signals[i][j]->write(SC_LOGIC_0);
			busy_PE_signals[i][j]->write(SC_LOGIC_0);
		}
	}
	switch (Pstate) {
	case S0:
		done->write(SC_LOGIC_1);
		init_iteration_cnt.write(SC_LOGIC_1);
		break;
	case S1:
		init_count.write(SC_LOGIC_1);
		for (int i = 0; i < mult_size; i++) {
			D_reg_load[i]->write(SC_LOGIC_1);
			R_reg_load[i]->write(SC_LOGIC_1);
			W_reg_load[i]->write(SC_LOGIC_1);
			for (int j = 0; j < mult_size; j++)
				start_PE_signals[i][j]->write(SC_LOGIC_1);
		}
		break;
	case S2:
		inc_count.write(SC_LOGIC_1);
		for (int i = 0; i < mult_size; i++) {
			W_reg_shift_en[i]->write(SC_LOGIC_1);
			for (int j = 0; j < mult_size; j++)
				start_PE_signals[i][j]->write(SC_LOGIC_1);
		}
		break;
	case S3:
		init_count.write(SC_LOGIC_1);
		break;
	case S4:
		inc_count.write(SC_LOGIC_1);
		for (int i = 0; i < mult_size; i++) {
			D_reg_shift_en[i]->write(SC_LOGIC_1);
			R_reg_shift_en[i]->write(SC_LOGIC_1);
			for (int j = 0; j < mult_size; j++)
				busy_PE_signals[i][j]->write(SC_LOGIC_1);
		}
		break;
	case S5:
		inc_iteration_cnt.write(SC_LOGIC_1);
		break;
	default:
		inc_count.write(SC_LOGIC_0);
		init_count.write(SC_LOGIC_0);
		init_iteration_cnt.write(SC_LOGIC_0);
		inc_iteration_cnt.write(SC_LOGIC_0);
		for (int i = 0; i < mult_size; i++) {
			D_reg_load[i]->write(SC_LOGIC_0);
			D_reg_shift_en[i]->write(SC_LOGIC_0);
			W_reg_load[i]->write(SC_LOGIC_0);
			W_reg_shift_en[i]->write(SC_LOGIC_0);
			R_reg_load[i]->write(SC_LOGIC_0);
			R_reg_shift_en[i]->write(SC_LOGIC_0);
			for (int j = 0; j < mult_size; j++) {
				start_PE_signals[i][j]->write(SC_LOGIC_0);
				busy_PE_signals[i][j]->write(SC_LOGIC_0);
			}
		}
		break;
	}

	Nstate = S0;
	switch (Pstate) {
	case S0:
		if (start == SC_LOGIC_0)
			Nstate = S0;
		else if (start == SC_LOGIC_1)
			Nstate = S1;
		break;
	case S1:
		Nstate = S2;
		break;
	case S2:
		if (count.read().to_uint() < mult_size-2)
			Nstate = S2;
		else
			Nstate = S3;
		break;
	case S3:
		Nstate = S4;
		break;
	case S4:
		if (count.read().to_uint() < 3 * mult_size - 1)
			Nstate = S4;
		else
			Nstate = S5;
		break;
	case S5:
		if (iteration_cnt.read().to_uint() < iteration_num - 1)
			Nstate = S1;
		else
			Nstate = S0;
		break;
	default:
		Nstate = S0;
		break;
	}
}

#endif // !MATRIX_MULT_CONTROLLER_MACRO