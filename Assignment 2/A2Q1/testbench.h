#include "systemc.h"
#include <iostream>
#include <iomanip>

using namespace std;

#define RDBYT 1
#define WTBYT 2
#define WTBLK 3
#define RDBLK 0
static sc_logic Z[8] = {SC_LOGIC_Z, SC_LOGIC_Z, SC_LOGIC_Z, SC_LOGIC_Z, SC_LOGIC_Z, SC_LOGIC_Z, SC_LOGIC_Z, SC_LOGIC_Z};

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

      //Read from byte and check data bus release
      cout << "Test 1: Read from byte" << endl;
      cout << "Expectations: data = XXXXXXXX" << endl;
      addr.write(0);
      comm.write(RDBYT);
      wait();
      new_comm.write(true);
      while(!complete.read()){
        wait();
      }
      data_read = data.read();
      cout << "@" << sc_time_stamp() << ": RDBYT, address = " << addr << ", data = " << data_read << endl;
      cout << endl;
      new_comm.write(false);
      wait();
      wait();

      cout << "Test 2: Checking Data bus is properely released" <<endl;
      cout << "Expectations: Data = ZZZZZZZZ" <<endl;
      data_read = data.read();
      cout << "@" << sc_time_stamp() << ": Data Release Check, data = " << data_read << endl;
      cout << endl;

      //Write to byte and check data bus release
      cout << "Test 3: Write to byte then read" << endl;
      cout << "Expectations: data = 11110000" << endl;
      data.write(0xF0);
      addr.write(1);
      comm.write(WTBYT);
      wait();
      new_comm.write(true);
      while(!complete.read()){
        wait();
      }
      new_comm.write(false);
      data.write(Z);
      wait();
      wait();

      comm.write(RDBYT);
      wait();
      new_comm.write(true);
      while(!complete.read()){
        wait();
      }
      new_comm.write(false);
      wait();
      wait();

      cout << endl << "Test 4: Checking Data Bus after test 3" <<endl;
      cout << "Expectations: Data = ZZZZZZZZ" <<endl;
      data_read = data.read();
      cout << "@" << sc_time_stamp() << ": Data Release Check, data = " << data_read << endl;
      cout << endl;

      //Read from block and check data bus release
      cout << "Test 5: Read from block" << endl;
      cout << "Expectations: data = XXXXXXXX, 1111000, XXXXXXXX, XXXXXXXX" << endl;
      addr.write(0);
      comm.write(RDBLK);
      wait();
      new_comm.write(true);
      while(!complete.read()){
        wait();
      }
      new_comm.write(false);
      wait();
      wait();

      cout << endl << "Test 6: Checking Data Bus after test 5" <<endl;
      cout << "Expectations: Data = ZZZZZZZZ" <<endl;
      data_read = data.read();
      cout << "@" << sc_time_stamp() << ": Data Release Check, data = " << data_read << endl;
      cout << endl;

      cout << "Test 7: Write to block then read" << endl;
      cout << "Expectations: data = 11000011, 11000011, 11000011, 11000011" << endl;
      data.write(0xC3);
      addr.write(230);
      comm.write(WTBLK);
      wait();
      new_comm.write(true);
      while(!complete.read()){
        wait();
      }
      new_comm.write(false);
      data.write(Z);
      wait();
      wait();

      cout<<endl<< "Test 8: Reading from block to check if write success @ address: " << addr << endl;
      cout << "Expectations: data = 11000011, 11000011, 11000011, 11000011" << endl;
      comm.write(RDBLK);
      wait();
      new_comm.write(true);
      while(!complete.read()){
        wait();
      }
      new_comm.write(false);
      wait();
      wait();

      cout << endl << "Test 9: Checking Data Bus after test 7 & 8" <<endl;
      cout << "Expectations: Data = ZZZZZZZZ" <<endl;
      data_read = data.read();
      cout << "@" << sc_time_stamp() << ": Data Release Check, data = " << data_read << endl;
      cout << endl;


      //Simulation end
      cout << "Tests Complete" << endl;
      sc_stop();
      wait();

    }
  }

  SC_CTOR(testbench){
    SC_CTHREAD(testbench1, clk.pos());
  }
};
