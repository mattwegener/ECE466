#include "systemc.h"
#include "stim.h"
#include "filter.h"
#include "mon.h"
#include <iostream>
#include <iomanip>

int sc_main(int argc, char* argv[])
{
    // Memory module instance:
    mem_ctrl MC("MC");
    
    // Your testbench module(s) instances:
    ...


    // Internal signals:
    sc_signal <bool> reset, new_comm, complete;
    sc_signal < sc_uint<2> > comm;
    sc_signal < sc_uint<8> > addr;
    sc_signal_rv <8> data;
    // _rv needed because of multiple drivers
  

    // Interconnects:
    MC.clk(clk);
    MC.reset(reset);
    MC.data(data);
    MC.addr(addr);
    MC.comm(comm);
    MC.new_comm(new_comm);
    MC.complete(complete);

    ...


    // Rest of sc_main ...

    return 0;
}
