#include "PE_TB.h"
#include "shift_reg_test.h"
#include "Matrix_Mult_TB1.h"
#include "Matrix_Mult_TB2.h"
#include "Matrix_Mult_TB3.h"
#include "BFM_Matrix_Mult_TB1.h"
#include "BFM_Matrix_Mult_TB2.h"
#include "BFM_Matrix_Mult_TB3.h"

int sc_main(int argc, char** argv) {
	
	PE_TB* test = new PE_TB("PE_TB_instance");
	sc_trace_file* VCD_PE;
	VCD_PE = sc_create_vcd_trace_file("PE_testbench");
	sc_trace(VCD_PE, test->clock, "clk");
	sc_trace(VCD_PE, test->reset, "rst");
	sc_trace(VCD_PE, test->start, "start");
	sc_trace(VCD_PE, test->busy_PE, "busyPE");
	sc_trace(VCD_PE, test->Din, "Din");
	sc_trace(VCD_PE, test->Dout, "Dout");
	sc_trace(VCD_PE, test->Win, "Win");
	sc_trace(VCD_PE, test->Wout, "Wout");
	sc_trace(VCD_PE, test->Sin, "Sin");
	sc_trace(VCD_PE, test->Sout, "Sout");

	
	shift_reg_test* TOP = new shift_reg_test("testbench_register");
	sc_trace_file* VCD_test_reg;
	VCD_test_reg = sc_create_vcd_trace_file("reg_test");
	sc_trace(VCD_test_reg, TOP->clock, "clk");
	sc_trace(VCD_test_reg, TOP->reset, "rst");
	sc_trace(VCD_test_reg, TOP->input_bus, "input");
	sc_trace(VCD_test_reg, TOP->parallel_in[0], "par_in0");
	sc_trace(VCD_test_reg, TOP->parallel_in[1], "par_in1");
	sc_trace(VCD_test_reg, TOP->parallel_in[2], "par_in2");
	sc_trace(VCD_test_reg, TOP->parallel_in[3], "par_in3");
	sc_trace(VCD_test_reg, TOP->parallel_out[0], "par_out0");
	sc_trace(VCD_test_reg, TOP->parallel_out[1], "par_out1");
	sc_trace(VCD_test_reg, TOP->parallel_out[2], "par_out2");
	sc_trace(VCD_test_reg, TOP->parallel_out[3], "par_out3");
	sc_trace(VCD_test_reg, TOP->load_register, "load_signal");
	sc_trace(VCD_test_reg, TOP->shift_enable, "shift_signal");
	
	Matrix_Mult_TB1* test_mult = new Matrix_Mult_TB1("test3");
	sc_trace_file* VCD_test_mult;
	VCD_test_mult = sc_create_vcd_trace_file("RTL_mult_test1");
	sc_trace(VCD_test_mult, test_mult->clk, "clk");
	sc_trace(VCD_test_mult, test_mult->rst, "rst");
	sc_trace(VCD_test_mult, test_mult->start, "start");
	sc_trace(VCD_test_mult, test_mult->done, "done");
	sc_trace(VCD_test_mult, test_mult->result_matrix[0][0], "result_11");
	sc_trace(VCD_test_mult, test_mult->result_matrix[0][1], "result_12");
	sc_trace(VCD_test_mult, test_mult->result_matrix[0][2], "result_13");
	sc_trace(VCD_test_mult, test_mult->result_matrix[1][0], "result_21");
	sc_trace(VCD_test_mult, test_mult->result_matrix[1][1], "result_22");
	sc_trace(VCD_test_mult, test_mult->result_matrix[1][2], "result_23");
	sc_trace(VCD_test_mult, test_mult->result_matrix[2][0], "result_31");
	sc_trace(VCD_test_mult, test_mult->result_matrix[2][1], "result_32");
	sc_trace(VCD_test_mult, test_mult->result_matrix[2][2], "result_33");

	Matrix_Mult_TB2* test2_mult = new Matrix_Mult_TB2("test2");
	sc_trace_file* VCD_test2_mult;
	VCD_test2_mult = sc_create_vcd_trace_file("RTL_mult_test2");
	sc_trace(VCD_test2_mult, test2_mult->clk, "clk");
	sc_trace(VCD_test2_mult, test2_mult->rst, "rst");
	sc_trace(VCD_test2_mult, test2_mult->start, "start");
	sc_trace(VCD_test2_mult, test2_mult->done, "done");
	sc_trace(VCD_test2_mult, test2_mult->result_matrix[0][0], "result_11");
	sc_trace(VCD_test2_mult, test2_mult->result_matrix[0][1], "result_12");
	sc_trace(VCD_test2_mult, test2_mult->result_matrix[0][2], "result_13");
	sc_trace(VCD_test2_mult, test2_mult->result_matrix[1][0], "result_21");
	sc_trace(VCD_test2_mult, test2_mult->result_matrix[1][1], "result_22");
	sc_trace(VCD_test2_mult, test2_mult->result_matrix[1][2], "result_23");
	sc_trace(VCD_test2_mult, test2_mult->result_matrix[2][0], "result_31");
	sc_trace(VCD_test2_mult, test2_mult->result_matrix[2][1], "result_32");
	sc_trace(VCD_test2_mult, test2_mult->result_matrix[2][2], "result_33");
	

	Matrix_Mult_TB3* test3_mult = new Matrix_Mult_TB3("test3");
	sc_trace_file* VCD_test3_mult;
	VCD_test3_mult = sc_create_vcd_trace_file("RTL_mult_test3");
	sc_trace(VCD_test3_mult, test3_mult->clk, "clk");
	sc_trace(VCD_test3_mult, test3_mult->rst, "rst");
	sc_trace(VCD_test3_mult, test3_mult->start, "start");
	sc_trace(VCD_test3_mult, test3_mult->done, "done");
	sc_trace(VCD_test3_mult, test3_mult->result_matrix[0][0], "result_11");
	sc_trace(VCD_test3_mult, test3_mult->result_matrix[0][1], "result_12");
	sc_trace(VCD_test3_mult, test3_mult->result_matrix[1][0], "result_21");
	sc_trace(VCD_test3_mult, test3_mult->result_matrix[1][1], "result_22");
	
	BFM_Matrix_Mult_TB1* test_BFM_mult = new BFM_Matrix_Mult_TB1("test_bfm_circuit");
	sc_trace_file* VCD_test_BFM_mult;
	VCD_test_BFM_mult = sc_create_vcd_trace_file("BFM_mult_test1");
	sc_trace(VCD_test_BFM_mult, test_BFM_mult->clk, "clk");
	sc_trace(VCD_test_BFM_mult, test_BFM_mult->rst, "rst");
	sc_trace(VCD_test_BFM_mult, test_BFM_mult->start, "start");
	sc_trace(VCD_test_BFM_mult, test_BFM_mult->done, "done");
	sc_trace(VCD_test_BFM_mult, test_BFM_mult->result_matrix[0][0], "result_11");
	sc_trace(VCD_test_BFM_mult, test_BFM_mult->result_matrix[0][1], "result_12");
	sc_trace(VCD_test_BFM_mult, test_BFM_mult->result_matrix[0][2], "result_13");
	sc_trace(VCD_test_BFM_mult, test_BFM_mult->result_matrix[1][0], "result_21");
	sc_trace(VCD_test_BFM_mult, test_BFM_mult->result_matrix[1][1], "result_22");
	sc_trace(VCD_test_BFM_mult, test_BFM_mult->result_matrix[1][2], "result_23");
	sc_trace(VCD_test_BFM_mult, test_BFM_mult->result_matrix[2][0], "result_31");
	sc_trace(VCD_test_BFM_mult, test_BFM_mult->result_matrix[2][1], "result_32");
	sc_trace(VCD_test_BFM_mult, test_BFM_mult->result_matrix[2][2], "result_33");

	BFM_Matrix_Mult_TB2* test2_BFM_mult = new BFM_Matrix_Mult_TB2("test2_bfm_circuit");
	sc_trace_file* VCD_test2_BFM_mult;
	VCD_test2_BFM_mult = sc_create_vcd_trace_file("BFM_mult_test2");
	sc_trace(VCD_test2_BFM_mult, test2_BFM_mult->clk, "clk");
	sc_trace(VCD_test2_BFM_mult, test2_BFM_mult->rst, "rst");
	sc_trace(VCD_test2_BFM_mult, test2_BFM_mult->start, "start");
	sc_trace(VCD_test2_BFM_mult, test2_BFM_mult->done, "done");
	sc_trace(VCD_test2_BFM_mult, test2_BFM_mult->result_matrix[0][0], "result_11");
	sc_trace(VCD_test2_BFM_mult, test2_BFM_mult->result_matrix[0][1], "result_12");
	sc_trace(VCD_test2_BFM_mult, test2_BFM_mult->result_matrix[0][2], "result_13");
	sc_trace(VCD_test2_BFM_mult, test2_BFM_mult->result_matrix[1][0], "result_21");
	sc_trace(VCD_test2_BFM_mult, test2_BFM_mult->result_matrix[1][1], "result_22");
	sc_trace(VCD_test2_BFM_mult, test2_BFM_mult->result_matrix[1][2], "result_23");
	sc_trace(VCD_test2_BFM_mult, test2_BFM_mult->result_matrix[2][0], "result_31");
	sc_trace(VCD_test2_BFM_mult, test2_BFM_mult->result_matrix[2][1], "result_32");
	sc_trace(VCD_test2_BFM_mult, test2_BFM_mult->result_matrix[2][2], "result_33");

	BFM_Matrix_Mult_TB3* test3_BFM_mult = new BFM_Matrix_Mult_TB3("test3_bfm_circuit");
	sc_trace_file* VCD_test3_BFM_mult;
	VCD_test3_BFM_mult = sc_create_vcd_trace_file("BFM_mult_test3");
	sc_trace(VCD_test3_BFM_mult, test3_BFM_mult->clk, "clk");
	sc_trace(VCD_test3_BFM_mult, test3_BFM_mult->rst, "rst");
	sc_trace(VCD_test3_BFM_mult, test3_BFM_mult->start, "start");
	sc_trace(VCD_test3_BFM_mult, test3_BFM_mult->done, "done");
	sc_trace(VCD_test3_BFM_mult, test3_BFM_mult->result_matrix[0][0], "result_11");
	sc_trace(VCD_test3_BFM_mult, test3_BFM_mult->result_matrix[0][1], "result_12");
	sc_trace(VCD_test3_BFM_mult, test3_BFM_mult->result_matrix[1][0], "result_21");
	sc_trace(VCD_test3_BFM_mult, test3_BFM_mult->result_matrix[1][1], "result_22");
	
	sc_start(1000, SC_NS);
	test3_mult->print_output_when_ready();
	test3_BFM_mult->print_result_when_ready();
	return 0;
}