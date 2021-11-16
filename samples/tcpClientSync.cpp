#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>

using namespace std;
using namespace boost;
using boost::asio::ip::tcp;

int main(int argc, char** argv)
{
  try {
    if (argc!=2) {
      cerr << "Usage: client <host>" << endl;
      return EXIT_FAILURE;
    }
    asio::io_context io_context;

    // Turn server name / ip into a TCP endpoint.

    tcp::resolver resolver(io_context);
    std::string hostName = argv[1];
    std::string serviceName{"daytime"};
    tcp::resolver::results_type endpoints = resolver.resolve(hostName, serviceName);

    cout << "enpoints size: " << endpoints.size() << endl;

    // now create and connect the socket
    tcp::socket socket(io_context);
    asio::connect(socket, endpoints);

    // The connection is open. Now we need to read the response from the daytime service

    for(;;) {
      boost::array<char, 128> buf;
      boost::system::error_code error;

      // asio::buffer() automatically determines the size of the array. It creates a non-modifiable buffer
      size_t len = socket.read_some(boost::asio::buffer(buf), error);

      // when the server closes the connection, read_some() will set EOF in error.
      if (error == asio::error::eof) {
        break;
      } else if (error) {
        throw system::system_error(error); // Some other error
      }

      cout.write(buf.data(), len);
    }
  } catch (std::exception& e) {
    cerr << "exception caught: " << e.what() << endl;
  }

  return EXIT_SUCCESS;
}
