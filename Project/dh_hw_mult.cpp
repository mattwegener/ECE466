#include "systemc.h"
#include "digit.h"
#include "dh_hw_mult.h"
#include <iostream>

void dh_hw_mult::process_hw_mult()
{

	//NN_DIGIT a[2];
	//NN_HALF_DIGIT bHigh, bLow, cHigh, cLow;

	for (;;) {
		switch(state){
			case WAIT: //wait for enable to be asserted
				if (hw_mult_enable.read()){
					exec = LOAD;
					state = EXECUTE;
				}
				break;

			case EXECUTE: //do multiplication
				switch(exec){
					case LOAD:
						b_load.write(true);
						c_load.write(true);
						a0_load.write(false);
						a1_load.write(false);
						exec = RUN;
						break;

					case RUN:
						b_load.write(false);
						c_load.write(false);
						a0_load.write(true);
						a1_load.write(true);
						exec = SEND;
						break;

					case SEND:
						a0_load.write(false);
						a1_load.write(false);
						state = OUTPUT;
					break;
				}

				break;

			case OUTPUT: //write to output port & assert done
				out_data_low.write(a0_out.read());
				out_data_high.write(a1_out.read());
				hw_mult_done.write(true);
				state = FINISH;
				break;

			case FINISH: //check for enable deassert -> deassert done
				if(!(hw_mult_enable.read())){
					hw_mult_done.write(false);
					// clear output signals
					out_data_low.write(0);
					out_data_high.write(0);
					state = WAIT;

				}
				break;

			default:
				break;
		}
		wait();
	}
}
