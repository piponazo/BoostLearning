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
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));

    for(;;){
      tcp::socket socket(io_service);
      acceptor.accept(socket);
      auto message = make_daytime_string();
      system::error_code ignored_error;
      asio::write(socket, asio::buffer(message), ignored_error);
    }
  }  catch (std::exception& e) {
    cerr << "Exception caught: " << e.what() << endl;
  }

  return EXIT_SUCCESS;
}
