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
    Tf->set_time_unit(1, SC_NS); // Time unit is 1 ns
    sc_trace(Tf, data, "data");
    sc_trace(Tf, addr, "addr");
    sc_trace(Tf, comm, "comm");
    sc_trace(Tf, new_comm, "new_comm");
    sc_trace(Tf, complete, "complete");
    sc_trace(Tf, reset, "reset");

    sc_start();  // run for 201 ns
    sc_close_vcd_trace_file(Tf);

    return 0;
}
