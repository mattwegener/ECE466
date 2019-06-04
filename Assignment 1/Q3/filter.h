#include "systemc.h"

SC_MODULE(filter2){
  sc_in<float> X;
  sc_in_clk clock;
  sc_in<bool> reset;
  sc_out<float> Y;

  sc_signal<float> R0in,R0out,R1in,R1out;


  void filter2(){
    Y.write(R1out.read()+(0.25*(R1out.read()+X.read)+0.5*R0out.read()));
    R0in.write(X.read()+(-1)*(0.25*(R1out.read()+X.read)+0.5*R0out.read()))
    R1in.write(R0out.read());
  }

  void zdelay(){
    while(true){
      if(reset == true){
        R0out.write(0);
        R1out.write(0);
      }
      else{
      R0out.write(R0in.read());
      R1out.write(R1in.read());
      }
      wait();
  }

  SC_CTOR(filter2){
    SC_METHOD(filter2);
    sensitive << X << R0out << R1out;
    SC_CTHREAD(zdelay, clock.pos());
  }

};