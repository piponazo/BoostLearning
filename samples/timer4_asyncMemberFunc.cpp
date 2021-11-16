#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
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
      : _timer(io, asio::chrono::seconds(1))
      , _count(0)
  {
    _timer.async_wait(bind(&Printer::print, this));
  }

  ~Printer()
  {
    std::cout << "Final count is " << _count << std::endl;
  }

  void print()
  {
    if (_count < 5) {
      cout << _count << endl;
      ++_count;
      _timer.expires_at(_timer.expiry() + asio::chrono::seconds(1));
      _timer.async_wait(boost::bind(&Printer::print, this));
    }
  }

private:
  asio::steady_timer _timer;
  int _count;
};

int main()
{
  cout << "App started..." << endl;
  asio::io_context io;
  Printer p(io);
  io.run();

  return EXIT_SUCCESS;
}
