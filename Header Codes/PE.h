#ifndef PE_MACRO
#define PE_MACRO

#include "PE_controller.h"
#include "PE_datapath.h"

SC_MODULE(PE) {
	sc_in<sc_logic>clock, reset;
	sc_in<sc_logic>strt, busy_PE;
	sc_in<sc_lv<8>>Din, Win;
	sc_in<sc_lv<24>>Sin;

	sc_out<sc_lv<8>>Dout, Wout;
	sc_out<sc_lv<24>>Sout;

	sc_signal<sc_logic>load_Win, load_Din, load_Sout;
	sc_signal<sc_logic>init_Win, init_Din, init_Sout;

	PE_controller* PE_cont;
	PE_datapath* PE_dtp;

	SC_CTOR(PE) {
		PE_cont = new PE_controller("controller");
		PE_cont->clk(clock);
		PE_cont->rst(reset);
		PE_cont->start(strt);
		PE_cont->busyPE(busy_PE);
		PE_cont->load_D(load_Din);
		PE_cont->load_W(load_Win);
		PE_cont->load_S(load_Sout);
		PE_cont->init_D(init_Din);
		PE_cont->init_W(init_Win);
		PE_cont->init_S(init_Sout);

		PE_dtp = new PE_datapath("datapath");
		PE_dtp->clk(clock);
		PE_dtp->rst(reset);
		PE_dtp->Si(Sin);
		PE_dtp->Di(Din);
		PE_dtp->Wi(Win);
		PE_dtp->So(Sout);
		PE_dtp->Do(Dout);
		PE_dtp->Wo(Wout);
		PE_dtp->load_D(load_Din);
		PE_dtp->load_W(load_Win);
		PE_dtp->load_S(load_Sout);
		PE_dtp->init_D(init_Din);
		PE_dtp->init_W(init_Win);
		PE_dtp->init_S(init_Sout);
	}

};
#endif