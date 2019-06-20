#include "systemc.h"

template <class T> class producer : public sc_module
{
  public:
    sc_port < fifo_out_if<T> > out;
    sc_in <bool> Clock;

    void do_writes()
    {
      T data = 0;
      while (true)
      {
        wait();
        if (out->write(data))
          cout << "W " << data << " at " << sc_time_stamp() << endl;
        if(data != 9) data++;
        else data = 0;

      }
    }
    SC_CTOR (producer) {
       SC_THREAD (do_writes);
       sensitive << Clock.pos();
    }

}
