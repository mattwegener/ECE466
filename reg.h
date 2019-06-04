#include "systemc.h"

SC_MODULE(reg){
  sc_in<float> in;
  sc_out<float> out;
  sc_in_clk clock;
  sc_in<bool> reset;

  //z delay register
  void do_reg(){
    while(1){
      if(reset.read() == true){
        out.write(0);
      }
      else
      {
        out.write(in.read());
      }
      wait();
    }
  }
  SC_CTOR(reg){
    SC_CTHREAD(do_reg,clock.pos());
  }
};
