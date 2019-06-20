#include "systemc.h"

template <class T, int size> class fifo : public sc_module, public fifo_out_if <T>, public fifo_in_if <T>
{
  private:
    T data[size];
    int free, ri, wi;	//free space, read/write index

    bool read_flag, write_flag, read_status, write_status;
    sc_event write_req, read_req, done;
    T* read_data;
    T write_data;

  public:
    SC_HAS_PROCESS (fifo);

    fifo (sc_module_name nm) : sc_module (nm)
    {
      free = size;
      ri = 0;
      wi = 0;
      read_flag = false;
      write_flag = false;
      read_status = false;
      write_status = false;
      SC_THREAD(arbitrator);
      sensitive << read_req << write_req;
    }

    void arbitrator() {
      while (1) {
        if (read_flag) { // read_flag first: Higher priority
          read_flag = false;

          if (free < size) { // service read
            *read_data = data[ri];
            ri = (ri + 1) % size;
            free++;
            read_status = true;
          }
          else read_status = false;
        }

        if (write_flag) { // write_flag Second: Lower priority
          write_flag = false;

          if (free > 0) { // service write
            data[wi] = write_data;
            wi = (wi + 1) % size;
            free--;
            write_status = true;
          }
          else write_status = false;
        }


        done.notify();
        wait();
      }//end while
    }//end func

    bool write(T data)
    {
      write_flag = true;
      write_data = data; // make a local copy of the input argument
      write_req.notify(); // pending event to trigger the arbitrator process
      wait(done); // arbitrator done: write serviced
      return write_status; // return a local copy of the output argument
    }

    bool read(T& data)
    {
      read_flag = true;
      read_data = &data; // make a local copy of the input argument
      read_req.notify(); // pending event to trigger the arbitrator process
      wait(done); // arbitrator done: read serviced
      return read_status; // return a local copy of the output argument
    }

};
