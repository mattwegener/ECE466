#include "systemc.h"

SC_MODULE(adder2){
  sc_in<float> A,B;
  sc_out<float> X;

  void do_adder2(){
    X.write(A.read() + B.read());
  }

  SC_CTOR(adder2){
    SC_METHOD(do_adder2);
    sensitive << A << B;
  }
};
