#include <iostream>
#include <boost/asio.hpp>

void print(const boost::system::error_code& e)
{
  std::cout << "Hello world!\n";
}

int main()
{
  std::cout << "App started..." << std::endl;
  boost::asio::io_context io;
  boost::asio::steady_timer t(io, boost::asio::chrono::seconds(2));

  // Using asio's asynchronous functionality means having a callback function that will be called when an asynchronous
  // operation completes.
  t.async_wait(&print);

  /* The asio library provides a guarantee that callback handlers will only be called from threads that are currently
  calling io_context::run(). Therefore unless the io_context::run() function is called the callback for the
  asynchronous wait completion will never be invoked.

  The io_context::run() function will also continue to run while there is still "work" to do. In this example, the
  work is the asynchronous wait on the timer, so the call will not return until the timer has expired and the callback
  has completed.

  It is important to remember to give the io_context some work to do before calling io_context::run(). For example,
  if we had omitted the above call to steady_timer::async_wait(), the io_context would not have had any work to do,
  and consequently io_context::run() would have returned immediately.
  */
  io.run();

  return EXIT_SUCCESS;
}
