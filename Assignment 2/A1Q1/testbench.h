#include "systemc.h"
#include <iostream>
#include <iomanip>

using namespace std;

#define RDBYT 1
#define WTBYT 2
#define WTBLK 3
#define RDBLK 0

SC_MODULE(testbench){
  sc_inout <sc_lv<8> > data; // Bidirectional port of logic-vector type
  sc_out < sc_uint<8> > addr;
  sc_out < sc_uint<2> > comm;
  sc_out <bool> new_comm; // Input port signaling “start”
  sc_in <bool> complete; // Output port signaling “done”
  sc_in_clk clk;
  sc_out <bool> reset;
  
  void testbench1(){
    // Temp variables for comparison
    sc_lv <8> data_read;

    // Reset system at start.
    reset.write(true); 
    wait();
    reset.write(false);
    wait();
    
    while(1){
      
    }
  }
  
  SC_CTOR(testbench){
    SC_CTHREAD(testbench1, clk.pos());
  }
};