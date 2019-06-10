#include "systemc.h"
#include "stimQ3.h"
#include "filterQ3.h"
#include "monQ3.h"
#include <iostream>
#include <iomanip>

int sc_main(int argc, char* argv[])
{
  sc_signal<float> Xin, Yout;
  sc_signal<bool> reset;
  sc_clock TestClk("TestClock", 10, SC_NS, 0.5, 1, SC_NS);

  stim Stim1 ("Stimulus");
  Stim1.X(Xin);
  Stim1.reset(reset);
  Stim1.Clk(TestClk);

  dig_filter DIT ("Filter");
  DIT.X(Xin);
  DIT.Y(Yout);
  DIT.clock(TestClk);
  DIT.reset(reset);

  mon Monitor1 ("Monitor");
  Monitor1.X(Xin);
  Monitor1.Y(Yout);
  Monitor1.Clk(TestClk);

  sc_trace_file* Tf = sc_create_vcd_trace_file("Filter_traces");
  Tf->set_time_unit(1, SC_NS);
  sc_trace(Tf, Xin  , "X" );
  sc_trace(Tf, Yout  , "Y" );
  sc_trace(Tf, reset, "RST");

  sc_start(201, SC_NS);  // run for 201 ns
  sc_close_vcd_trace_file(Tf);

  return 0;
}
