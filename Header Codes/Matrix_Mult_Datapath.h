#ifndef MATRIX_MULT_DATAPATH_MACRO
#define MATRIX_MULT_DATAPATH_MACRO

#include <systemc.h>
#include "shift_reg.h"
#include "PE.h"

template<int multiplier_size>
SC_MODULE(Matrix_Mult_Datapath) {
	sc_in<sc_logic>clk, rst;
	sc_in< sc_lv<8> > W_matrix[multiplier_size][multiplier_size];
	sc_in< sc_lv<8> > D_matrix[multiplier_size][multiplier_size];
	sc_out< sc_lv<24> > result_matrix[multiplier_size][multiplier_size];

	shift_reg<2 * multiplier_size - 1,8> *D_reg[multiplier_size];
	sc_signal< sc_lv<8> >D_reg_par_load[multiplier_size][2 * multiplier_size - 1];
	sc_signal< sc_lv<8> >D_reg_par_out[multiplier_size][2 * multiplier_size - 1];
	sc_signal< sc_lv<8> >D_reg_serin[multiplier_size];
	sc_in< sc_logic >D_reg_load[multiplier_size];
	sc_in< sc_logic >D_reg_shift_en[multiplier_size];

	shift_reg<multiplier_size,8> *W_reg[multiplier_size];
	sc_signal< sc_lv<8> >W_reg_par_load[multiplier_size][multiplier_size];
	sc_signal< sc_lv<8> >W_reg_par_out[multiplier_size][multiplier_size];
	sc_signal< sc_lv<8> >W_reg_serin[multiplier_size];
	sc_in< sc_logic >W_reg_load[multiplier_size];
	sc_in< sc_logic >W_reg_shift_en[multiplier_size];

	shift_reg<3 * multiplier_size - 2,24>*R_reg[multiplier_size];
	sc_signal< sc_lv<24> >R_reg_par_load[multiplier_size][3 * multiplier_size -2];
	sc_signal< sc_lv<24> >R_reg_par_out[multiplier_size][3 * multiplier_size -2];
	sc_signal< sc_lv<24> >R_reg_serin[multiplier_size];
	sc_in< sc_logic >R_reg_load[multiplier_size];
	sc_in< sc_logic >R_reg_shift_en[multiplier_size];

	PE *processing_elements[multiplier_size][multiplier_size];
	sc_signal< sc_lv<8> >D_internal[multiplier_size+1][multiplier_size];
	sc_signal< sc_lv<8> >W_internal[multiplier_size][multiplier_size+1];
	sc_signal< sc_lv<24> >sum_internal[multiplier_size][multiplier_size+1];
	sc_in< sc_logic >start_PE_signals[multiplier_size][multiplier_size];
	sc_in< sc_logic >busy_PE_signals[multiplier_size][multiplier_size];

	SC_CTOR(Matrix_Mult_Datapath) {
		SC_METHOD(D_reg_binding);
		for(int i=0 ; i<multiplier_size ; i++)
			for(int j=0 ; j<multiplier_size ; j++)
				sensitive << D_matrix[i][j];
		//SC_THREAD(D_reg_instanciation);
		for (int i = 0; i < multiplier_size; i++) {
			shift_reg<2 * multiplier_size - 1, 8>* new_D_reg = new shift_reg<2 * multiplier_size - 1, 8>("shift_D_reg");
			new_D_reg->clk(clk);
			new_D_reg->rst(rst);
			new_D_reg->shift_en(D_reg_shift_en[i]);
			new_D_reg->load_reg(D_reg_load[i]);
			for (int j = 0; j < 2 * multiplier_size - 1; j++) {
				new_D_reg->par_in[j](D_reg_par_load[i][j]);
				new_D_reg->par_out[j](D_reg_par_out[i][j]);
			}
			new_D_reg->input(D_reg_serin[i]);
			D_reg[i] = new_D_reg;
		}

		SC_METHOD(W_reg_binding);
		for (int i = 0; i < multiplier_size; i++)
			for (int j = 0; j < multiplier_size; j++)
				sensitive << W_matrix[i][j];
		//SC_THREAD(W_reg_instanciation);
		for (int i = 0; i < multiplier_size; i++) {
			shift_reg<multiplier_size, 8>* new_W_reg;
			new_W_reg = new shift_reg<multiplier_size, 8>("shift_W_reg");
			new_W_reg->clk(clk);
			new_W_reg->rst(rst);
			new_W_reg->shift_en(W_reg_shift_en[i]);
			new_W_reg->load_reg(W_reg_load[i]);
			for (int j = 0; j < multiplier_size; j++) {
				new_W_reg->par_in[j](W_reg_par_load[i][j]);
				new_W_reg->par_out[j](W_reg_par_out[i][j]);
			}
			new_W_reg->input(W_reg_serin[i]);
			W_reg[i] = new_W_reg;
		}

		SC_METHOD(R_reg_binding);
		for (int i = 0; i < multiplier_size; i++)
			for (int j = 0; j < 3*multiplier_size; j++)
				sensitive << R_reg_par_out[i][j];
		//SC_THREAD(R_reg_instanciation);
		for (int i = 0; i < multiplier_size; i++) {
			shift_reg<3 * multiplier_size - 2, 24>* new_R_reg;
			new_R_reg = new shift_reg<3 * multiplier_size - 2, 24>("shift_R_reg");
			new_R_reg->clk(clk);
			new_R_reg->rst(rst);
			new_R_reg->shift_en(R_reg_shift_en[i]);
			new_R_reg->load_reg(R_reg_load[i]);
			for (int j = 0; j < 3 * multiplier_size - 2; j++) {
				new_R_reg->par_in[j](R_reg_par_load[i][j]);
				new_R_reg->par_out[j](R_reg_par_out[i][j]);
			}
			new_R_reg->input(R_reg_serin[i]);
			R_reg[i] = new_R_reg;
		}

		SC_METHOD(PE_binding);
		for (int i = 0; i < multiplier_size; i++)
			sensitive << D_reg_par_out[i][2 * multiplier_size - 2] << W_reg_par_out[i][multiplier_size - 1] << sum_internal[i][multiplier_size];
		//SC_THREAD(PE_instanciation);
		for (int i = 0; i < multiplier_size; i++) {
			for (int j = 0; j < multiplier_size; j++) {
				PE* first_PE = new PE("first_processing_element");
				first_PE->clock(clk);
				first_PE->reset(rst);
				first_PE->strt(start_PE_signals[i][j]);
				first_PE->busy_PE(busy_PE_signals[i][j]);
				first_PE->Din(D_internal[i][j]);
				first_PE->Dout(D_internal[i+1][j]);
				first_PE->Win(W_internal[i][j]);
				first_PE->Wout(W_internal[i][j + 1]);
				first_PE->Sin(sum_internal[i][j]);
				first_PE->Sout(sum_internal[i][j + 1]);
				processing_elements[i][j] = first_PE;
			}
		}
	}
	void D_reg_binding();
	//void D_reg_instanciation();
	void W_reg_binding();
	//void W_reg_instanciation();
	void R_reg_binding();
	//void R_reg_instanciation();
	//void PE_instanciation();
	void PE_binding();
};

template<int multiplier_size>
void Matrix_Mult_Datapath<multiplier_size>::D_reg_binding() {
	for (int i = 0; i < multiplier_size; i++) {
		int matrix_index = multiplier_size - 1;
		for (int j = 0; j < 2 * multiplier_size - 1; j++) {
			if (j < multiplier_size - 1 - i)
				D_reg_par_load[i][j] = 0;
			else if (j < 2 * multiplier_size - 1 - i) {
				D_reg_par_load[i][j] = D_matrix[i][matrix_index];
				matrix_index--;
			}
			else
				D_reg_par_load[i][j] = 0;
		}
		D_reg_serin[i] = 0;
	}
}
/*
template<int multiplier_size>
void Matrix_Mult_Datapath<multiplier_size>::D_reg_instanciation() {
	for (int i = 0; i < multiplier_size; i++) {
		shift_reg<2 * multiplier_size - 1, 8>* new_D_reg = new shift_reg<2 * multiplier_size - 1, 8>("shift_D_reg");
		new_D_reg->clk(clk);
		new_D_reg->rst(rst);
		new_D_reg->shift_en(D_reg_shift_en[i]);
		new_D_reg->load_reg(D_reg_load[i]);
		for (int j = 0; j < 2 * multiplier_size - 1; j++) {
			new_D_reg->par_in[j](D_reg_par_load[i][j]);
			new_D_reg->par_out[j](D_reg_par_out[i][j]);
		}
		new_D_reg->input(D_reg_serin[i]);
		D_reg[i] = new_D_reg;
	}
}
*/


template<int multiplier_size>
void Matrix_Mult_Datapath<multiplier_size>::W_reg_binding() {
	for (int i = 0; i < multiplier_size; i++) {
		for (int j = 0; j < multiplier_size; j++)
			W_reg_par_load[i][j] = W_matrix[i][j];
		W_reg_serin[i] = 0;
	}
}


/*
template<int multiplier_size>
void Matrix_Mult_Datapath<multiplier_size>::W_reg_instanciation() {
	for (int i = 0; i < multiplier_size; i++) {
		shift_reg<multiplier_size, 8>* new_W_reg;
		new_W_reg = new shift_reg<multiplier_size, 8>("shift_W_reg");
		new_W_reg->clk(clk);
		new_W_reg->rst(rst);
		new_W_reg->shift_en(W_reg_shift_en[i]);
		new_W_reg->load_reg(W_reg_load[i]);
		for (int j = 0; j < multiplier_size; j++) {
			new_W_reg->par_in[j](W_reg_par_load[i][j]);
			new_W_reg->par_out[j](W_reg_par_out[i][j]);
		}
		new_W_reg->input(W_reg_serin[i]);
		W_reg[i] = new_W_reg;
	}
}
*/

/*
template<int multiplier_size>
void Matrix_Mult_Datapath<multiplier_size>::R_reg_instanciation() {
	for (int i = 0; i < multiplier_size; i++) {
		shift_reg<3*multiplier_size-2, 24>* new_R_reg;
		new_R_reg = new shift_reg<3*multiplier_size-2, 24>("shift_R_reg");
		new_R_reg->clk(clk);
		new_R_reg->rst(rst);
		new_R_reg->shift_en(R_reg_shift_en[i]);
		new_R_reg->load_reg(R_reg_load[i]);
		for (int j = 0; j < 3 * multiplier_size - 2; j++) {
			new_R_reg->par_in[j](R_reg_par_load[i][j]);
			new_R_reg->par_out[j](R_reg_par_out[i][j]);
		}
		new_R_reg->input(R_reg_serin[i]);
		R_reg[i] = new_R_reg;
	}
}
*/

template<int multiplier_size>
void Matrix_Mult_Datapath<multiplier_size>::R_reg_binding() {
	for (int i = 0; i < multiplier_size; i++) {
		int matrix_index = multiplier_size-1;
		for (int j = 0; j < 3 * multiplier_size - 2; j++) {
			if ((j >= multiplier_size - 1 - i) && (j < 2 * multiplier_size - 1 - i)) {
				result_matrix[i][matrix_index] = R_reg_par_out[i][j];
				matrix_index--;
			}
			R_reg_par_load[i][j] = 0;
		}
	}
}

/*
template<int multiplier_size>
void Matrix_Mult_Datapath<multiplier_size>::PE_instanciation() {
	for (int i = 0; i < multiplier_size; i++) {
		for (int j = 0; j < multiplier_size; j++) {
			PE* first_PE = new PE("first_processing_element");
			first_PE->clock(clk);
			first_PE->reset(rst);
			first_PE->strt(start_PE_signals[i][j]);
			first_PE->busy_PE(busy_PE_signals[i][j]);
			first_PE->Din(D_internal[i][j]);
			first_PE->Dout(D_internal[i][j+1]);
			first_PE->Win(W_internal[i][j]);
			first_PE->Wout(W_internal[i][j + 1]);
			first_PE->Sin(sum_internal[i][j]);
			first_PE->Sout(sum_internal[i][j + 1]);
			processing_elements[i][j] = first_PE;
		}

	}
}
*/

template<int multiplier_size>
void Matrix_Mult_Datapath<multiplier_size>::PE_binding() {
	for (int i = 0; i < multiplier_size; i++) {
		D_internal[0][i] = D_reg_par_out[i][2 * multiplier_size - 2];
		W_internal[i][0] = W_reg_par_out[i][multiplier_size - 1];
		R_reg_serin[i] = sum_internal[i][multiplier_size];
		sum_internal[i][0] = 0;
	}
}

#endif // !MATRIX_MULT_DATAPATH_MACRO