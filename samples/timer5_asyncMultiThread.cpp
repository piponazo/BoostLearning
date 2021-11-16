#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>

/*
In this tutorial we will see how to use a class member function as a callback handler.
The program should execute identically to the tutorial program from tutorial Timer.3.
*/

using namespace std;
using namespace boost;

class Printer
{
public:
  Printer(asio::io_context& io)
      : _strand(asio::make_strand(io))
      , _timer1(io, asio::chrono::seconds(1)) // 2 timers in parallel
      , _timer2(io, asio::chrono::seconds(1))
      , _count(0)
  {
    // The boost::asio::bind_executor() function returns a new handler that automatically dispatches its contained
    // handler through the strand object. By binding the handlers to the same strand, we are ensuring that they cannot
    // execute concurrently.
    _timer1.async_wait(asio::bind_executor(_strand, bind(&Printer::print1, this)));
    _timer2.async_wait(asio::bind_executor(_strand, bind(&Printer::print2, this)));
  }

  ~Printer()
  {
    std::cout << "Final count is " << _count << std::endl;
  }

  void print1()
  {
    if (_count < 10) {
      cout << "Timer 1: " << _count << endl;
      ++_count;
      _timer1.expires_at(_timer1.expiry() + asio::chrono::seconds(1));
      _timer1.async_wait(asio::bind_executor(_strand, bind(&Printer::print1, this)));
    }
  }

  void print2()
  {
    if (_count < 10) {
      cout << "Timer 2: " << _count << endl;
      ++_count;
      _timer2.expires_at(_timer2.expiry() + asio::chrono::seconds(1));
      _timer2.async_wait(asio::bind_executor(_strand, bind(&Printer::print2, this)));
    }
  }

private:
  asio::strand<asio::io_context::executor_type> _strand;
  asio::steady_timer _timer1;
  asio::steady_timer _timer2;
  int _count;
};

int main()
{
  cout << "App started..." << endl;
  asio::io_context io;
  Printer p(io);

  // io_context::run() is now called from two threads: the main thread and one additional thread.

  boost::thread t(bind(&boost::asio::io_context::run, &io));
  io.run();
  t.join();

  return EXIT_SUCCESS;
}
