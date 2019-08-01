#include "systemc.h"
#include "digit.h"
#include "dh_hw_mult.h"

void dh_hw_mult::process_hw_mult()
{

	NN_DIGIT a[2];
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
						b_load.write(TRUE);
						c_load.write(TRUE);
						a0_load.write(FALSE);
						a1_load.write(FALSE);
						exec = RUN;
						break;

					case RUN:
						b_load.write(FALSE);
						c_load.write(FALSE);
						a0_load.write(TRUE);
						a1_load.write(TRUE);
						exec = SEND;
						break;

					case SEND:
						a0_load.write(FALSE);
						a1_load.write(FALSE);
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
