#ifndef PE_CONTROLLER_MACRO
#define PE_CONTROLLER_MACRO

#include <systemc.h>

SC_MODULE(PE_controller) {
	sc_in<sc_logic>clk, rst;
	sc_in<sc_logic>start, busyPE;
	sc_out<sc_logic>init_W, init_D, init_S, load_W, load_S, load_D;
	enum states{S0,S1,S2,S3};
	sc_signal<states>Nstate, Pstate;

	SC_CTOR(PE_controller) {
		SC_METHOD(sequential_part);
			sensitive << clk << rst;

		SC_METHOD(combinential_part);
			sensitive << Pstate << start << busyPE;
	}
	void sequential_part();
	void combinential_part();
};
#endif // !PE_CONTROLLER_MACRO