#include <iostream>
#include <boost/asio.hpp>

int main()
{
  const int secs {1};
  // All programs that use asio need to have at least one I/O execution context, such as an io_context
  // or thread_pool object. An I/O execution context provides access to I/O functionality.
  boost::asio::io_context io;

  // The core asio classes that provide I/O functionality (or as in this case timer functionality) always take a
  // reference to an io_context as their first constructor argument
  boost::asio::steady_timer t(io, boost::asio::chrono::seconds(secs));

  std::cout << "In " << secs << " seconds you will see something more..." << std::endl;

  // A timer is always in one of two states: "expired" or "not expired". If the steady_timer::wait() function is
  // called on an expired timer, it will return immediately.
  t.wait();

  std::cout << "Hello world!\n";
  return EXIT_SUCCESS;
}
