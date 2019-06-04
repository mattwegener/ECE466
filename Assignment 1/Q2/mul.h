#include "systemc.h"

SC_MODULE(mul){
  sc_in<float> A,CST;
  sc_out<float> M;

  void do_mul(){
    M.write(A.read() * CST);
  }

  SC_CTOR(mul){
    SC_METHOD(do_mul);
    sensitive << A;
  }
};
