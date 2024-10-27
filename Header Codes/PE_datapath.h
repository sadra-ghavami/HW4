#ifndef PE_DATAPATH_MACRO
#define PE_DATAPATH_MACRO

#include <systemc.h>

SC_MODULE(PE_datapath)
{
	sc_in<sc_logic>	rst;
	sc_in<sc_logic>	clk;
	sc_in<sc_lv<8>> Di;
	sc_in<sc_lv<8>> Wi;
	sc_in<sc_lv<24>> Si;
	sc_in<sc_logic> load_D, load_W, load_S;
	sc_in<sc_logic>	init_W, init_D, init_S;

	sc_out<sc_lv<8>> Do;
	sc_out<sc_lv<8>> Wo;
	sc_out<sc_lv<24>> So;

	sc_signal<sc_lv<16>>mult_out;
	sc_signal<sc_lv<24>>add_out;

	SC_CTOR(PE_datapath)
	{
		SC_METHOD(registering_Wi);
		sensitive << rst << clk;

		SC_METHOD(registering_Di);
		sensitive << rst << clk;

		SC_METHOD(registering_So);
		sensitive << rst << clk;

		SC_METHOD(adding);
		sensitive << Si << mult_out;

		SC_METHOD(multiplying);
		sensitive << Do << Wo;
	}
	void registering_Wi();
	void registering_Di();
	void registering_So();
	void adding();
	void multiplying();
};
#endif // !PE_DATAPATH_MACRO

