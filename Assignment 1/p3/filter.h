#include "systemc.h"

SC_MODULE(filter){
  sc_in<float> X;
  sc_in_clk clock;
  sc_in<bool> reset;
  sc_out<float> Y;

};
