#include "systemc.h"
#include "digit.h"

SC_MODULE(adder2){
  sc_in<NN_DIGIT> A,B;
  sc_out<NN_DIGIT> C;

  void do_adder2(){
    C.write(A.read() + B.read());
  }

  SC_CTOR(adder2){
    SC_METHOD(do_adder2);
    sensitive << A << B;
  }
};

SC_MODULE(mul2){
  sc_in<NN_DIGIT> A,B;
  sc_out<NN_DIGIT> M;

  void do_mul2(){
    M.write(A.read() * B.read());
  }

  SC_CTOR(mul2){
    SC_METHOD(do_mul2);
    sensitive << A << B;
  }
};


SC_MODULE(reg){
  sc_in<NN_DIGIT> in;
  sc_out<NN_DIGIT> out;
  sc_in_clk clock;
  sc_in<bool> load;

  void do_reg(){
    while(true){
      if(load.read()
        out.write(in.read());
      }
      wait();
    }
  }
  SC_CTOR(reg){
    SC_CTHREAD(do_reg,clock.pos());
  }
};

SC_MODULE(mux2){
    sc_in<NN_DIGIT> in1,in2;
    sc_out<NN_DIGIT> out;
    sc_in<bool> sel;

    void do_mux2(){
        if(sel.read()) out.write(in1.read());
        else out.write(in2.read());
    }

    SC_CTOR(mux2){
        SC_METHOD(do_mux2);
        sensitive << in1 << in2 << sel;
    }
};

SC_MODULE(t2){
    sc_in<NN_DIGIT> in1, in2;
    sc_out<bool> lt;

    void do_lt2(){
        if(in1 < in2) lt.write(true);
        else lt.write(false);
    }

    SC_CTOR(lt2){
        SC_METHOD(do_lt2);
        sensitive << in1 << in2;
    }
};

SC_MODULE(splitter_32){
    sc_in<NN_DIGIT> input;
    sc_out<NN_DIGIT> high,low;

    void do_spliiter_32(){
        high.write((NN_HALF_DIGIT)HIGH_HALF (input.read()));
        low.write((NN_HALF_DIGIT)LOW_HALF (input.read()));
    }

    SC_CTOR(spliiter_32){
        SC_METHOD(do_splitter_32);
        sensitive << input;
    }
};

SC_MODULE(LSR_high){
    sc_in<NN_DIGIT> in;
    sc_out<NN_DIGIT> out;

    void do_LSR_high(){
        out.write(TO_HIGH_HALF(in.read()));
    }

    SC_CTOR(LSR_high){
        SC_METHOD(do_LSR_high);
        sensitive << in;
    }
};

SC_MODULE(mask_high){
    sc_in<NN_DIGIT> in;
    sc_out<NN_DIGIT> out;

    void do_mask_high(){
        out.write(HIGH_HALF(in.read()));
    }

    SC_CTOR(mask_high){
        SC_METHOD(do_mask_high);
        sensitive << in;
    }
};
