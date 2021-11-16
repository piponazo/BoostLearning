#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

/*
In this tutorial we will modify the program from tutorial Timer.2 so that the timer fires once a second.
This will show how to pass additional parameters to your handler function.
*/

using namespace std;
using namespace boost;

void print(const system::error_code& e, asio::steady_timer* timer, int* count)
{
  if (*count < 5){
    cout << *count << endl;
    ++(*count);
    timer->expires_at(timer->expiry() + asio::chrono::seconds(1));
    timer->async_wait(boost::bind(print, asio::placeholders::error, timer, count)); // Start new async wait
  }
  // After counter's value is 6, we do not give more work to do to the io_context
}

int main()
{
  cout << "App started..." << endl;
  asio::io_context io;

  int count{0};
  asio::steady_timer t(io, asio::chrono::seconds(1));
  t.async_wait(boost::bind(print, asio::placeholders::error, &t, &count));
  io.run();

  cout << "Final value: " << count << endl;

  return EXIT_SUCCESS;
}
