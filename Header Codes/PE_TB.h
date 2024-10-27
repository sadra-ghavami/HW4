#ifndef PE_TB_MACRO
#define PE_TB_MACRO


#include "PE.h"

SC_MODULE(PE_TB) {
	sc_signal<sc_logic>clock, reset;
	sc_signal<sc_logic>start, busy_PE;
	sc_signal<sc_lv<8>>Din, Win;
	sc_signal<sc_lv<8>>Dout, Wout;
	sc_signal<sc_lv<24>>Sin, Sout;

	PE* TOP;

	SC_CTOR(PE_TB) {
		TOP = new PE("PE_instance");
		TOP->clock(clock);
		TOP->reset(reset);
		TOP->strt(start);
		TOP->busy_PE(busy_PE);
		TOP->Din(Din);
		TOP->Dout(Dout);
		TOP->Win(Win);
		TOP->Wout(Wout);
		TOP->Sin(Sin);
		TOP->Sout(Sout);
		
		SC_THREAD(clk_generating);
		SC_THREAD(reset_assertion);
		SC_THREAD(input_generating);
	}
	void clk_generating();
	void reset_assertion();
	void input_generating();
};

#endif // !PE_TB_MACRO

