#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <ctime>
#include <iostream>
#include <string>

using namespace boost;
using boost::asio::ip::tcp;

std::string make_daytime_string()
{
  using namespace std;  // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

class tcp_connection : public boost::enable_shared_from_this<tcp_connection>
{
public:
  typedef boost::shared_ptr<tcp_connection> pointer;

  static pointer create(boost::asio::io_context& io_context)
  {
    return pointer(new tcp_connection(io_context));
  }

  tcp::socket& socket()
  {
    return socket_;
  }

  void start()
  {
    message_ = make_daytime_string();

    // Using async_write to ensure that the entire block of data is sent
    asio::async_write(socket_, asio::buffer(message_),
                      boost::bind(&tcp_connection::handle_write, shared_from_this(), asio::placeholders::error,
                                  asio::placeholders::bytes_transferred));
  }

private:
  tcp_connection(asio::io_context& io_context)
      : socket_(io_context)
  {
  }

  void handle_write(const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/)
  {
  }

  tcp::socket socket_;
  std::string message_;
};

class tcp_server
{
public:
  tcp_server(asio::io_context& io_context)
      : io_context_(io_context)
      , acceptor_(io_context, tcp::endpoint(tcp::v4(), 13))
  {
    start_accept();
  }

private:
  void start_accept()
  {
    // Create a socket and initiates an async accept operation to wait for a new connection
    tcp_connection::pointer newConn = tcp_connection::create(io_context_);
    acceptor_.async_accept(newConn->socket(),
                           boost::bind(&tcp_server::handle_accept, this, newConn, asio::placeholders::error));
  }

  void handle_accept(tcp_connection::pointer newConn, const boost::system::error_code& error)
  {
    if (!error) {
      newConn->start();
    }

    start_accept();
  }

  asio::io_context& io_context_;
  tcp::acceptor acceptor_;
};

int main()
{
  try {
    asio::io_context io_context;
    tcp_server server(io_context);
    io_context.run();
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
