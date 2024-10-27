#include "PE_datapath.h"

void PE_datapath::adding() {
	sc_lv<24>result;
	result = Si->read().to_uint() + mult_out.read().to_uint();
	add_out.write(result);
}

void PE_datapath::multiplying() {
	sc_lv<16>result;
	result = Do->read().to_uint() * Wo->read().to_uint();
	mult_out.write(result);
}

void PE_datapath::registering_Wi(){
	if (rst->read() == SC_LOGIC_1)
		Wo = "00000000";
	else if (clk->event() && clk == "1") {
		if (init_W == SC_LOGIC_1)
			Wo = "00000000";
		else if (load_W == SC_LOGIC_1)
			Wo = Wi;
	}
}

void PE_datapath::registering_Di() {
	if (rst->read() == SC_LOGIC_1)
		Do = "00000000";
	else if (clk->event() && clk == SC_LOGIC_1) {
		if (init_D == SC_LOGIC_1)
			Do = "00000000";
		else if (load_D == SC_LOGIC_1)
			Do = Di;
	}
}

void PE_datapath::registering_So() {
	if (rst->read() == SC_LOGIC_1)
		So = "000000000000000000000000";
	else if (clk->event() && clk == SC_LOGIC_1) {
		if (init_S == SC_LOGIC_1)
			So = "000000000000000000000000";
		else if (load_S == SC_LOGIC_1)
			So = add_out;
	}
}
