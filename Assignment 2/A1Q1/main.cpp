#include "systemc.h"
#include "testbench.h"
#include "mem_ctrl.h"
#include <iostream>
#include <iomanip>

int sc_main(int argc, char* argv[])
{
    // Internal signals:
    sc_signal <bool> reset, new_comm, complete;
    sc_signal < sc_uint<2> > comm;
    sc_signal < sc_uint<8> > addr;
    sc_signal_rv <8> data;
    sc_clock clk("TestClock", 10, SC_NS, 0.5, 1, SC_NS);
    // _rv needed because of multiple drivers
    
    // Memory module instance:
    mem_ctrl MC("MC");
    testbench TB("Testbench");


    // Interconnects:
    TB.data(data);
    TB.addr(addr);
    TB.comm(comm);
    TB.new_comm(new_comm);
    TB.complete(complete);
    TB.clk(clk);
    TB.reset(reset);
    
    MC.clk(clk);
    MC.reset(reset);
    MC.data(data);
    MC.addr(addr);
    MC.comm(comm);
    MC.new_comm(new_comm);
    MC.complete(complete);


    // Rest of sc_main ...
    sc_trace_file* Tf = sc_create_vcd_trace_file("Filter_traces");
    Tf->set_time_unit(1, SC_NS);
    /*
    sc_trace(Tf, Xin  , "X" );
    sc_trace(Tf, Yout  , "Y" );
    sc_trace(Tf, reset, "RST");
    */
    sc_start(201, SC_NS);  // run for 201 ns
    sc_close_vcd_trace_file(Tf);

    return 0;
}
