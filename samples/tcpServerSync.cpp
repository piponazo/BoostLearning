#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using namespace std;
using namespace boost;
using boost::asio::ip::tcp;

std::string make_daytime_string()
{
  time_t now = time(0);
  return ctime(&now);
}

int main()
{
  try {
    asio::io_service io_service;

    // tcp::acceptor listen for new connections.
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));

    // Iterative server (handling one connection at a time).
    for(;;){
      // Create a socket that will represent the connection to the client. Then wait for a connection.
      tcp::socket socket(io_service);
      acceptor.accept(socket);

      // Once connected, obtain the time and transfer the information to the client.
      auto message = make_daytime_string();
      system::error_code ignored_error;
      asio::write(socket, asio::buffer(message), ignored_error);
    }
  }  catch (std::exception& e) {
    cerr << "Exception caught: " << e.what() << endl;
  }

  return EXIT_SUCCESS;
}
