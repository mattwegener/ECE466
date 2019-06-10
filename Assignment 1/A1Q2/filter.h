#include "systemc.h"
#include "adder.h"
#include "mul.h"
#include "reg.h"

SC_MODULE(filter){
  sc_in<float> X;
  sc_out<float> Y;
  sc_in_clk clock;
  sc_in<bool> reset;

  adder2 ADD0, ADD1, ADD2, ADD3;
  mul MULT0, MULT1, MULT2;
  reg REG0, REG1;

  sc_signal<float> a0,a1,a2;
  sc_signal<float> R0out, R1out, M0out, M1out, M2out;
  sc_signal<float> A0out, A1out, A2out, A3out;

  SC_CTOR(filter):
    ADD0("adder0"), ADD1("adder1"), ADD2("adder2"), ADD3("adder3"),MULT0("multiplier0"),
    MULT1("multiplier1"), MULT2("multiplier2"), REG0("register0"), REG1("register1") {

    REG0.reset(reset); REG0.clock(clock); REG0.in(A0out); REG0.out(R0out);
    REG1.reset(reset); REG1.clock(clock); REG1.in(R0out); REG1.out(R1out);

    MULT0.CST(a0); MULT0.A(A1out); MULT0.M(M0out);
    MULT1.CST(a1); MULT1.A(R0out); MULT1.M(M1out);
    MULT2.CST(a2); MULT2.A(A2out); MULT2.M(M2out);

    ADD0.A(X); ADD0.B(M0out); ADD0.C(A0out);
    ADD1.A(M1out); ADD1.B(M2out); ADD1.C(A1out);
    ADD2.A(X); ADD2.B(R1out); ADD2.C(A2out);
    ADD3.A(A1out); ADD3.B(R1out); ADD3.C(Y);

    a0.write(-1);
    a1.write(0.5);
    a2.write(0.25);
  }

};
