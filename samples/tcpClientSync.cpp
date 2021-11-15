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
    tcp::resolver resolver(io_context);

    tcp::resolver::results_type endpoints = resolver.resolve(argv[1], "daytime");

    tcp::socket socket(io_context);
    asio::connect(socket, endpoints);

    for(;;) {
      boost::array<char, 128> buf;
      boost::system::error_code error;
      size_t len = socket.read_some(boost::asio::buffer(buf), error);

      if (error == asio::error::eof) {
        break;
      } else if (error) {
        throw system::system_error(error); // Some other error
      }

      cout.write(buf.data(), len);
    }
  } catch (std::exception& e) {
    cerr << e.what() << endl;
  }

  return EXIT_SUCCESS;
}
