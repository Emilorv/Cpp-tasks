#include <boost/asio.hpp>
#include <iostream>

using namespace std;
using namespace boost::asio::ip;

class WebServer {
private:
  class Connection {
  public:
    tcp::socket socket;
    Connection(boost::asio::io_service &io_service) : socket(io_service) {}
  };

  boost::asio::io_service io_service;

  tcp::endpoint endpoint;
  tcp::acceptor acceptor;

  void handle_request(shared_ptr<Connection> connection) {
    auto read_buffer = make_shared<boost::asio::streambuf>();
    // Read from client until newline ("\r\n")
    async_read_until(connection->socket, *read_buffer, "\r\n",
                     [this, connection, read_buffer](const boost::system::error_code &ec, size_t) {
                       // If not error:
                       if (!ec) {
                         // Retrieve message from client as string:
                         istream read_stream(read_buffer.get());
                         std::string message;
                         getline(read_stream, message);
                         message.pop_back(); // Remove "\r" at the end of message

                         if (message.find("GET / HTTP/1.1") != std::string::npos) {
                           send_response(connection, "HTTP/1.1 200 OK \r\n\r\n Dette er hovedssiden");
                         } else if (message.find("GET /en_side HTTP/1.1") != std::string::npos) {
                           send_response(connection, "HTTP/1.1 200 OK \r\n\r\n Dette er en side");
                         } else {
                           send_response(connection, "HTTP/1.1 404 Not Found \r\n\e\n 404 Not Found");
                         }
                       }
                     });
  }

  void send_response(shared_ptr<Connection> connection, string message) {
    auto write_buffer = make_shared<boost::asio::streambuf>();
    ostream write_stream(write_buffer.get());

    // Add message to be written to client:
    write_stream << message << "\r\n";

    // Write to client
    async_write(connection->socket, *write_buffer,
                [connection, write_buffer](const boost::system::error_code &ec, size_t) {
                  if (!ec) {
                    connection->socket.close();
                  }
                });
  }
  void accept() {
    // The (client) connection is added to the lambda parameter and handle_request
    // in order to keep the object alive for as long as it is needed.
    auto connection = make_shared<Connection>(io_service);

    // Accepts a new (client) connection. On connection, immediately start accepting a new connection
    acceptor.async_accept(connection->socket, [this, connection](const boost::system::error_code &ec) {
      accept();
      // If not error:
      if (!ec) {
        handle_request(connection);
      }
    });
  }

public:
  WebServer() : endpoint(tcp::v4(), 8080), acceptor(io_service, endpoint) {}

  void start() {
    accept();

    io_service.run();
  }
};

int main() {
  WebServer web_server;
  cout << "Web server started. Connect with http://localhost:8080" << endl;
  web_server.start();
}
