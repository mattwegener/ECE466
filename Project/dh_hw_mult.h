#include "systemc.h"
#include "digit.h"
#include "hw_IC.h"

#ifndef _DH_HW_MULT_H_
#define _DH_HW_MULT_H_ 1

SC_MODULE (dh_hw_mult)
{
  sc_in<bool> hw_mult_enable;
  sc_in<NN_DIGIT> in_data_1;
  sc_in<NN_DIGIT> in_data_2;
  sc_in_clk clk;

  sc_out<NN_DIGIT> out_data_low;
  sc_out<NN_DIGIT> out_data_high;
  sc_out<bool> hw_mult_done;

  //HW ICs needed for hw multiple
  adder2 add1, add2, add3, add4, add5;
  mul2 mult1, mult2, mult3, mult4;
  splitter_32 splitter_b, splitter_c;
  reg b_reg, c_reg, a0_reg, a1_reg;
  lt2 if1, if2;
  mask_high HH1;
  LSR_high LSR1, LSR2;
  mux2 muxer1, muxer2;

  //signals required by hw mult
  sc_signal<NN_DIGIT> b, c ,bhigh, blow,chigh, clow, a0, a1, t, u; //reg, splliter and mult signals
  sc_signal<bool> lt_1, lt_2; // comp signals
  sc_signal<bool> b_load, c_load, a0_load, a1_load; //reg timing signals
  sc_signal<NN_DIGIT> t_u, a1_hh1, u_hht, a0_out, a1_1, a1_out, hh_1, hh_t; //adder & LSR signals
  sc_signal<NN_DIGIT> m1_a1, m2_a1, t_mask; //mux and mask signals

  enum state {WAIT,EXECUTE,OUTPUT,FINISH} state;

  void process_hw_mult();

  SC_CTOR (dh_hw_mult)
  {
      SC_CTHREAD (process_hw_mult, clk.pos());
      state = WAIT;
      NN_DIGIT one = 1;
      //input
      b_reg.in(in_data_1); b_reg.out(b); b_reg.load(b_load); b_reg.clock(clk);
      c_reg.in(in_data_2); c_reg.out(c); c_reg.load(c_load); c_reg.clock(clk);

      //split data
      splitter_b.input(b); splitter_b.high(bhigh); splitter_b.low(blow);
      splitter_c.input(c); splitter_c.high(chigh); splitter_b.low(clow);

      //mult data
      mult1.A(blow); mult1.B(clow); mult1.M(a0);
      mult2.A(blow); mult2.B(chigh); mult2.M(t);
      mult3.A(bhigh); mult3.B(clow); mult3.M(u);
      mult4.A(bhigh); mult4.B(chigh); mult4.M(a1);

      //inputs for 1st comp
      add1.A(t); add1.B(u); add1.C(t_u);
      if1.in1(t_u); if1.in2(u); if1.lt(lt_1);

      //LSRS
      LSR1.in(one); LSR1.out(hh_1);
      LSR2.in(t_u); LSR2.out(hh_t);

      //mux1
      add2.A(hh_1); add2.B(a1); add2.C(a1_hh1);
      muxer1.in1(a1_hh1); muxer1.in2(a1); muxer1.sel(lt_1); muxer1.out(m1_a1);

      //a0 output
      add3.A(hh_t); add3.B(a0); add3.C(a0_out);

      //lt comparator 2
      if2.in1(a0_out); if2.in2(hh_t); if2.lt(lt_2);

      //mux2
      add4.A(m1_a1); add4.B(one); add4.C(a1_1);
      muxer2.in1(a1_1); muxer2.in2(m1_a1); muxer2.sel(lt_2); muxer2.out(m2_a1);

      //a1 output
      HH1.in(t_u); HH1.out(t_mask);
      add5.A(m2_a1); add5.B(t_mask); add5.C(a1_out);

  }

};

#endif /* end _DH_HW_MULT_H_ */
