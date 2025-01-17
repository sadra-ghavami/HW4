#include "BFM_Matrix_Mult_TB1.h"

void BFM_Matrix_Mult_TB1::clk_generation() {
	while (true) {
		clk = SC_LOGIC_0;
		wait(10, SC_NS);
		clk = SC_LOGIC_1;
		wait(10, SC_NS);
	}
}

void BFM_Matrix_Mult_TB1::rst_generation() {
	rst = SC_LOGIC_0;
	wait(2, SC_NS);
	rst = SC_LOGIC_1;
	wait(5, SC_NS);
	rst = SC_LOGIC_0;
}

void BFM_Matrix_Mult_TB1::input_generation() {
	D_matrix[0][0] = 4; D_matrix[1][0] = 16; D_matrix[2][0] = 2;
	D_matrix[0][1] = 2; D_matrix[1][1] = 12; D_matrix[2][1] = 1;
	D_matrix[0][2] = 8; D_matrix[1][2] = 10; D_matrix[2][2] = 0;

	W_matrix[0][0] = 5; W_matrix[1][0] = 3; W_matrix[2][0] = 2;
	W_matrix[0][1] = 1; W_matrix[1][1] = 8; W_matrix[2][1] = 2;
	W_matrix[0][2] = 4; W_matrix[1][2] = 16; W_matrix[2][2] = 4;
	start = SC_LOGIC_0;
	wait(20, SC_NS);
	start = SC_LOGIC_1;
	wait(20, SC_NS);
	start = SC_LOGIC_0;
	wait(800, SC_NS);

}

void BFM_Matrix_Mult_TB1::print_result_when_ready() {
	if (done == SC_LOGIC_1) {
		cout << "result BFM test1: " << endl;
		for (int i = 0; i < 3; i++) {
			cout << result_matrix[0][i].read().to_uint();
			for (int j = 1; j < 3; j++) {
				cout << " , " << result_matrix[j][i].read().to_uint();
			}
			cout << endl;
		}
	}
}