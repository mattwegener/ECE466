#include "systemc.h"
#include "digit.h"
#include "dh_hw_mult.h"

void dh_hw_mult::process_hw_mult()
{

	NN_DIGIT a[2], b, c, t, u;
	NN_HALF_DIGIT bHigh, bLow, cHigh, cLow;

	for (;;) {
		switch(state){
			case WAIT: //wait for enable to be asserted
				if (hw_mult_enable.read()){
					state = EXECUTE;
				}
				break;

			case EXECUTE: //do multiplication
				// Read inputs
				b = in_data_1.read();
				c = in_data_2.read();

				// Original code from NN_DigitMult()...
				bHigh = (NN_HALF_DIGIT)HIGH_HALF (b);
				bLow = (NN_HALF_DIGIT)LOW_HALF (b);
				cHigh = (NN_HALF_DIGIT)HIGH_HALF (c);
				cLow = (NN_HALF_DIGIT)LOW_HALF (c);

				a[0] = (NN_DIGIT)bLow * (NN_DIGIT)cLow;
				t = (NN_DIGIT)bLow * (NN_DIGIT)cHigh;
				u = (NN_DIGIT)bHigh * (NN_DIGIT)cLow;
				a[1] = (NN_DIGIT)bHigh * (NN_DIGIT)cHigh;

				if ((t += u) < u) a[1] += TO_HIGH_HALF (1);

				u = TO_HIGH_HALF (t);

				if ((a[0] += u) < u) a[1]++;

				a[1] += HIGH_HALF (t);

				state = OUTPUT;
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
					state = WAIT;
				}
				break;

			default:
				break;
		}
		wait();
	}
}
