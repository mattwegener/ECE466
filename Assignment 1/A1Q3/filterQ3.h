#include "systemc.h"

SC_MODULE(dig_filter){
  sc_in<float> X;
  sc_in_clk clock;
  sc_in<bool> reset;
  sc_out<float> Y;

  sc_signal<float> R0in,R0out,R1in,R1out;


  void do_filter(){
    Y.write(R1out.read()+(0.25*(R1out.read()+X.read())+0.5*R0out.read()));
    R0in.write(X.read()-(0.25*(R1out.read()+X.read())+0.5*R0out.read()));
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
  }

    SC_CTOR(dig_filter){
    SC_METHOD(do_filter);
    sensitive << X << R0out << R1out;
    SC_CTHREAD(zdelay, clock.pos());
  }

};
