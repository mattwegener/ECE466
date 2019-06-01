#include "systemc.h"

SC_MODULE(adder2){
  sc_in<float> A,B;
  sc_out<float> C;

  void do_adder2(){
    C.write(A.read() + B.read());
  }

  SC_CTOR(adder2){
    SC_METHOD(do_adder2);
    sensitive << A << B;
  }
};
