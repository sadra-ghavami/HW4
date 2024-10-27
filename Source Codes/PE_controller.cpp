#include "PE_controller.h"

void PE_controller::combinential_part() {
	if (Pstate == S0) {
		if (start == SC_LOGIC_0)
			Nstate = S0;
		else if (start == SC_LOGIC_1)
			Nstate = S1;
	}
	else if (Pstate == S1) {
		if (start == SC_LOGIC_0)
			Nstate = S2;
		else if (start == SC_LOGIC_1)
			Nstate = S1;
	}
	else if (Pstate == S2) {
		if (busyPE == SC_LOGIC_0)
			Nstate = S2;
		else if (busyPE == SC_LOGIC_1)
			Nstate = S3;
	}
	else if (Pstate == S3) {
		if (busyPE == SC_LOGIC_0)
			Nstate = S0;
		else if (busyPE == SC_LOGIC_1)
			Nstate = S3;
	}


	init_W->write(SC_LOGIC_0);
	init_D->write(SC_LOGIC_0);
	init_S->write(SC_LOGIC_0);
	load_W->write(SC_LOGIC_0);
	load_D->write(SC_LOGIC_0);
	load_S->write(SC_LOGIC_0);
	if (Pstate == S0) {
		init_W->write(SC_LOGIC_1);
		init_D->write(SC_LOGIC_1);
		init_S->write(SC_LOGIC_1);
	}
	else if (Pstate == S1) {
		load_W->write(SC_LOGIC_1);
	}
	else if (Pstate == S2) {
		load_D->write(SC_LOGIC_1);
	}
	else if (Pstate == S3) {
		load_S->write(SC_LOGIC_1);
		load_D->write(SC_LOGIC_1);
	}
}

void PE_controller::sequential_part() {
	if (rst == SC_LOGIC_1) {
		Pstate = S0;
		//Nstate = S0;
	}
	else if (clk->event() && clk == SC_LOGIC_1) {
		Pstate = Nstate;
	}
}