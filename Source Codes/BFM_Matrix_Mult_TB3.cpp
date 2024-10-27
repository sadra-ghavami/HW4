#include "BFM_Matrix_Mult_TB3.h"

void BFM_Matrix_Mult_TB3::clk_generation() {
	while (true) {
		clk = SC_LOGIC_0;
		wait(10, SC_NS);
		clk = SC_LOGIC_1;
		wait(10, SC_NS);
	}
}

void BFM_Matrix_Mult_TB3::rst_generation() {
	rst = SC_LOGIC_0;
	wait(2, SC_NS);
	rst = SC_LOGIC_1;
	wait(5, SC_NS);
	rst = SC_LOGIC_0;
}

void BFM_Matrix_Mult_TB3::input_generation() {
	D_matrix[0][0] = 4; D_matrix[1][0] = 10;
	D_matrix[0][1] = 7; D_matrix[1][1] = 13;

	W_matrix[0][0] = 5; W_matrix[1][0] = 3;
	W_matrix[0][1] = 6; W_matrix[1][1] = 15;

	start = SC_LOGIC_0;
	wait(20, SC_NS);
	start = SC_LOGIC_1;
	wait(20, SC_NS);
	start = SC_LOGIC_0;
	wait(60, SC_NS);
	D_matrix[0][0] = 11; D_matrix[1][0] = 12;
	D_matrix[0][1] = 8; D_matrix[1][1] = 5;
	wait(220, SC_NS);
	final_result[0][0] = result_matrix[0][0]; final_result[1][0] = result_matrix[1][0];
	final_result[0][1] = result_matrix[0][1]; final_result[1][1] = result_matrix[1][1];
	wait(400, SC_NS);
	final_result[0][2] = result_matrix[0][0]; final_result[1][2] = result_matrix[1][0];
	final_result[0][3] = result_matrix[0][1]; final_result[1][3] = result_matrix[1][1];
	wait(200, SC_NS);

}

void BFM_Matrix_Mult_TB3::print_result_when_ready() {
	if (done == SC_LOGIC_1) {
		cout << "result BFM test3 : " << endl;
		for (int i = 0; i < 4; i++) {
			cout << final_result[0][i].read().to_uint();
			cout << " , " ;
			cout << final_result[1][i].read().to_uint();
			cout << endl;
		}
	}
}