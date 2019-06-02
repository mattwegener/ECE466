#include "systemc.h"
#include <iomanip>

SC_MODULE(stim)
{
  sc_out<float> X;
  sc_out<bool> reset;
  sc_in_clk Clk;

  void stimgen()
  {
    //initial reset
    reset.write(true);
    wait();
    //1 cycle unit pulse
    X.write(1);
    wait();
    //20 Data points after unit pulse
    for(int i = 0;i<19;i++){
      X.write(0);
      wait();
    }
    sc_stop();
  }
  SC_CTOR(stim)
  {
    SC_CTHREAD(stimgen, Clk.pos());
  }
};
