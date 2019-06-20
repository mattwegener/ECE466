#include "systemc.h"
#include "fifo_if.h"
#include "fifo.h"
#include "producer.h"
#include "consumer.h"
#include <iostream>
#include <iomanip>

int sc_main(int argc, char* argv[]){
	sc_clock ClkFast ("ClkFast", 50,  SC_NS, 0.5, 1, SC_NS);
	sc_clock ClkSlow ("ClkSlow", 100, SC_NS, 0.5, 1, SC_NS);

  fifo Fifo1 (”F1”, 8); // 8-character FIFO
  producer P1 ("P1"); P1.out (Fifo1); P1.Clock (ClkFast);
  consumer C1 ("C1"); C1.in (Fifo1); C1.Clock (ClkSlow);


  sc_start (1001, SC_NS);

return 0;
}
