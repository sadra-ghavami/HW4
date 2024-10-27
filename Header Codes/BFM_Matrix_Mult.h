#ifndef BFM_MATRIX_MULT_MACRO
#define BFM_MATRIX_MULT_MACRO
#include <systemc.h>

template<int mult_size, int iteration_num>
SC_MODULE(BFM_Matrix_Mult) {
	sc_in<sc_logic>clk, rst, start;
	sc_out<sc_logic>done;
	sc_in< sc_lv<8> > W_matrix[mult_size][mult_size];
	sc_in< sc_lv<8> > D_matrix[mult_size][mult_size];
	sc_out< sc_lv<24> > result_matrix[mult_size][mult_size];


	SC_CTOR(BFM_Matrix_Mult) {
		SC_THREAD(calculating);
		sensitive << clk << rst;
	}
	void calculating();
};

template<int mult_size, int iteration_num>
void BFM_Matrix_Mult<mult_size, iteration_num>::calculating() {
	while (true) {
		if (rst == SC_LOGIC_1) {
			done = SC_LOGIC_0;
			for (int i = 0; i < mult_size; i++)
				for (int j = 0; j < mult_size; j++)
					result_matrix[i][j] = 0;
		}
		else if (clk->event() && clk == SC_LOGIC_1) {
			done = SC_LOGIC_1;
			if (start == SC_LOGIC_1) {
				for (int n = 0; n < iteration_num; n++) {
					done = SC_LOGIC_0;
					sc_lv<24>result[mult_size][mult_size];
					for (int i = 0; i < mult_size; i++) {
						for (int j = 0; j < mult_size; j++) {
							sc_uint<24> sum = 0;
							for (int k = 0; k < mult_size; k++)
								sum = sum + D_matrix[k][i]->read().to_uint() * W_matrix[j][k]->read().to_uint();
							result[j][i] = sum;
						}
					}
					for (int i = 0; i < 4 * mult_size + 2; i++)
						wait(clk->posedge_event());
					for (int i = 0; i < mult_size; i++)
						for (int j = 0; j < mult_size; j++)
							result_matrix[i][j] = result[i][j];

					if(n == iteration_num-1)
						done = SC_LOGIC_1;
					else
						wait(clk->posedge_event());
				}
			}
		}
		wait();
	}
}



#endif 