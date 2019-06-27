#include "systemc.h"

SC_MODULE(dig_filter){
  sc_in<float> X;
  sc_in_clk clock;
  sc_out<float> Y;

  sc_signal<float> R1,R2,R3,R4,R5,R6,R7;

  void filter(){
    while(1){
      Y.write(0.026526*(R1.read()+R7.read())-0.238732*(R3.read()+R5.read())+0.5*R4.read());
      R7.write(R6.read());
      R6.write(R5.read());
      R5.write(R4.read());
      R4.write(R3.read());
      R3.write(R2.read());
      R2.write(R1.read());
      R1.write(X.read());
      wait();
    }
  }

  SC_CTOR(dig_filter){
    SC_CTHREAD(filter, clock.pos());
    R1.write(0);R2.write(0);R3.write(0);R4.write(0);
    R5.write(0);R6.write(0);R7.write(0);
    Y.initialize(0);
  }

};
