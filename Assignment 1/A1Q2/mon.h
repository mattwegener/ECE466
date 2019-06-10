#include "systemc.h"
#include <iostream>
#include <iomanip>
using namespace std;

SC_MODULE(mon)
{
  sc_in<float> X, Y;
  //sc_in<bool> reset;
  sc_in<bool> Clk;

  void monitor() {
  	cout << setw(10) << "Time";
  	cout << setw(2) << "X" << setw(14) << "Y" << endl;

  	while (true) {
  		cout << setw(10) << sc_time_stamp();
  		cout << setw(2) << X.read() << setw(14) << Y.read();
  		cout << endl;
  		wait();
  	}
  }

  SC_CTOR(mon){
    SC_THREAD(monitor);
    sensitive << X << Y;
    dont_initialize();
  }
};
