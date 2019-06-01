#include "systemc.h"

SC_MODULE(mul_cst){
  sc_in<float> A,CST;
  sc_out<float> M;

  void do_mul_cst(){
    M.write(A.read() * CST);
  }

  SC_CTOR(mul_cst){
    SC_METHOD(do_mul_cst);
    sensitive << A;
  }
};
