#include "big_file.hpp"

#include "connection.hpp"
#include <utility>
#include <vector>
#include "connection_manager.hpp"
#include "request_handler.hpp"

namespace http {
    namespace server {

        connection::connection(boost::asio::ip::tcp::socket socket,
                               connection_manager& manager, request_handler& handler, database_manager& db_manager)
                : socket_(std::move(socket)),
                  connection_manager_(manager),
                  request_handler_(handler),
                  database_manager_(db_manager)
        {
        }

        void connection::start()
        {
            do_read();
        }

        void connection::stop()
        {
            socket_.close();
        }

        void connection::do_read()
        {
            auto self(shared_from_this());
            socket_.async_read_some(boost::asio::buffer(buffer_),
                                    [this, self](boost::system::error_code ec, std::size_t bytes_transferred)
                                    {
                                        if (!ec)
                                        {
                                            request_parser::result_type result;
                                            std::tie(result, std::ignore) = request_parser_.parse(
                                                    request_, buffer_.data(), buffer_.data() + bytes_transferred);

                                            if (result == request_parser::good)
                                            {
                                                request_handler_.handle_request(request_, reply_, database_manager_);
                                                do_write();
                                            }
                                            else if (result == request_parser::bad)
                                            {
                                                reply_ = reply::stock_reply(reply::bad_request);
                                                do_write();
                                            }
                                            else
                                            {
                                                do_read();
                                            }
                                        }
                                        else if (ec != boost::asio::error::operation_aborted)
                                        {
                                            connection_manager_.stop(shared_from_this());
                                        }
                                    });
        }

        void connection::do_write()
        {
            auto self(shared_from_this());
            boost::asio::async_write(socket_, reply_.to_buffers(),
                                     [this, self](boost::system::error_code ec, std::size_t)
                                     {
                                         if (!ec)
                                         {
                                             // Initiate graceful connection closure.
                                             boost::system::error_code ignored_ec;
                                             socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both,
                                                              ignored_ec);
                                         }

                                         if (ec != boost::asio::error::operation_aborted)
                                         {
                                             connection_manager_.stop(shared_from_this());
                                         }
                                     });
        }

    } // namespace server
} // namespace http



// _________________________________________________________________


#include "reply.hpp"
#include <string>

namespace http {
    namespace server {

        namespace status_strings {

            const std::string ok =
                    "HTTP/1.0 200 OK\r\n";
            const std::string created =
                    "HTTP/1.0 201 Created\r\n";
            const std::string accepted =
                    "HTTP/1.0 202 Accepted\r\n";
            const std::string no_content =
                    "HTTP/1.0 204 No Content\r\n";
            const std::string multiple_choices =
                    "HTTP/1.0 300 Multiple Choices\r\n";
            const std::string moved_permanently =
                    "HTTP/1.0 301 Moved Permanently\r\n";
            const std::string moved_temporarily =
                    "HTTP/1.0 302 Moved Temporarily\r\n";
            const std::string not_modified =
                    "HTTP/1.0 304 Not Modified\r\n";
            const std::string bad_request =
                    "HTTP/1.0 400 Bad Request\r\n";
            const std::string unauthorized =
                    "HTTP/1.0 401 Unauthorized\r\n";
            const std::string forbidden =
                    "HTTP/1.0 403 Forbidden\r\n";
            const std::string not_found =
                    "HTTP/1.0 404 Not Found\r\n";
            const std::string internal_server_error =
                    "HTTP/1.0 500 Internal Server Error\r\n";
            const std::string not_implemented =
                    "HTTP/1.0 501 Not Implemented\r\n";
            const std::string bad_gateway =
                    "HTTP/1.0 502 Bad Gateway\r\n";
            const std::string service_unavailable =
                    "HTTP/1.0 503 Service Unavailable\r\n";

            boost::asio::const_buffer to_buffer(reply::status_type status)
            {
                switch (status)
                {
                    case reply::ok:
                        return boost::asio::buffer(ok);
                    case reply::created:
                        return boost::asio::buffer(created);
                    case reply::accepted:
                        return boost::asio::buffer(accepted);
                    case reply::no_content:
                        return boost::asio::buffer(no_content);
                    case reply::multiple_choices:
                        return boost::asio::buffer(multiple_choices);
                    case reply::moved_permanently:
                        return boost::asio::buffer(moved_permanently);
                    case reply::moved_temporarily:
                        return boost::asio::buffer(moved_temporarily);
                    case reply::not_modified:
                        return boost::asio::buffer(not_modified);
                    case reply::bad_request:
                        return boost::asio::buffer(bad_request);
                    case reply::unauthorized:
                        return boost::asio::buffer(unauthorized);
                    case reply::forbidden:
                        return boost::asio::buffer(forbidden);
                    case reply::not_found:
                        return boost::asio::buffer(not_found);
                    case reply::internal_server_error:
                        return boost::asio::buffer(internal_server_error);
                    case reply::not_implemented:
                        return boost::asio::buffer(not_implemented);
                    case reply::bad_gateway:
                        return boost::asio::buffer(bad_gateway);
                    case reply::service_unavailable:
                        return boost::asio::buffer(service_unavailable);
                    default:
                        return boost::asio::buffer(internal_server_error);
                }
            }

        } // namespace status_strings

        namespace misc_strings {

            const char name_value_separator[] = { ':', ' ' };
            const char crlf[] = { '\r', '\n' };

        } // namespace misc_strings

        std::vector<boost::asio::const_buffer> reply::to_buffers()
        {
            std::vector<boost::asio::const_buffer> buffers;
            buffers.push_back(status_strings::to_buffer(status));
            for (std::size_t i = 0; i < headers.size(); ++i)
            {
                header& h = headers[i];
                buffers.push_back(boost::asio::buffer(h.name));
                buffers.push_back(boost::asio::buffer(misc_strings::name_value_separator));
                buffers.push_back(boost::asio::buffer(h.value));
                buffers.push_back(boost::asio::buffer(misc_strings::crlf));
            }
            buffers.push_back(boost::asio::buffer(misc_strings::crlf));
            buffers.push_back(boost::asio::buffer(content));
            return buffers;
        }

        namespace stock_replies {

            const char ok[] = "";
            const char created[] =
                    "<html>"
                    "<head><title>Created</title></head>"
                    "<body><h1>201 Created</h1></body>"
                    "</html>";
            const char accepted[] =
                    "<html>"
                    "<head><title>Accepted</title></head>"
                    "<body><h1>202 Accepted</h1></body>"
                    "</html>";
            const char no_content[] =
                    "<html>"
                    "<head><title>No Content</title></head>"
                    "<body><h1>204 Content</h1></body>"
                    "</html>";
            const char multiple_choices[] =
                    "<html>"
                    "<head><title>Multiple Choices</title></head>"
                    "<body><h1>300 Multiple Choices</h1></body>"
                    "</html>";
            const char moved_permanently[] =
                    "<html>"
                    "<head><title>Moved Permanently</title></head>"
                    "<body><h1>301 Moved Permanently</h1></body>"
                    "</html>";
            const char moved_temporarily[] =
                    "<html>"
                    "<head><title>Moved Temporarily</title></head>"
                    "<body><h1>302 Moved Temporarily</h1></body>"
                    "</html>";
            const char not_modified[] =
                    "<html>"
                    "<head><title>Not Modified</title></head>"
                    "<body><h1>304 Not Modified</h1></body>"
                    "</html>";
            const char bad_request[] =
                    "<html>"
                    "<head><title>Bad Request</title></head>"
                    "<body><h1>400 Bad Request</h1></body>"
                    "</html>";
            const char unauthorized[] =
                    "<html>"
                    "<head><title>Unauthorized</title></head>"
                    "<body><h1>401 Unauthorized</h1></body>"
                    "</html>";
            const char forbidden[] =
                    "<html>"
                    "<head><title>Forbidden</title></head>"
                    "<body><h1>403 Forbidden</h1></body>"
                    "</html>";
            const char not_found[] =
                    "<html>"
                    "<head><title>Not Found</title></head>"
                    "<body><h1>404 Not Found</h1></body>"
                    "</html>";
            const char internal_server_error[] =
                    "<html>"
                    "<head><title>Internal Server Error</title></head>"
                    "<body><h1>500 Internal Server Error</h1></body>"
                    "</html>";
            const char not_implemented[] =
                    "<html>"
                    "<head><title>Not Implemented</title></head>"
                    "<body><h1>501 Not Implemented</h1></body>"
                    "</html>";
            const char bad_gateway[] =
                    "<html>"
                    "<head><title>Bad Gateway</title></head>"
                    "<body><h1>502 Bad Gateway</h1></body>"
                    "</html>";
            const char service_unavailable[] =
                    "<html>"
                    "<head><title>Service Unavailable</title></head>"
                    "<body><h1>503 Service Unavailable</h1></body>"
                    "</html>";

            std::string to_string(reply::status_type status)
            {
                switch (status)
                {
                    case reply::ok:
                        return ok;
                    case reply::created:
                        return created;
                    case reply::accepted:
                        return accepted;
                    case reply::no_content:
                        return no_content;
                    case reply::multiple_choices:
                        return multiple_choices;
                    case reply::moved_permanently:
                        return moved_permanently;
                    case reply::moved_temporarily:
                        return moved_temporarily;
                    case reply::not_modified:
                        return not_modified;
                    case reply::bad_request:
                        return bad_request;
                    case reply::unauthorized:
                        return unauthorized;
                    case reply::forbidden:
                        return forbidden;
                    case reply::not_found:
                        return not_found;
                    case reply::internal_server_error:
                        return internal_server_error;
                    case reply::not_implemented:
                        return not_implemented;
                    case reply::bad_gateway:
                        return bad_gateway;
                    case reply::service_unavailable:
                        return service_unavailable;
                    default:
                        return internal_server_error;
                }
            }

        } // namespace stock_replies

        reply reply::stock_reply(reply::status_type status)
        {
            reply rep;
            rep.status = status;
            rep.content = stock_replies::to_string(status);
            rep.headers.resize(2);
            rep.headers[0].name = "Content-Length";
            rep.headers[0].value = std::to_string(rep.content.size());
            rep.headers[1].name = "Content-Type";
            rep.headers[1].value = "text/html";
            return rep;
        }

    } // namespace server
} // namespace http


// _________________________________________________________________


#include "request_handler.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "mime_types.hpp"
#include "reply.hpp"
#include "request.hpp"

namespace http {
    namespace server {

        request_handler::request_handler(const std::string& doc_root)
                : doc_root_(doc_root)
        {
        }

        void request_handler::handle_request(const request& req, reply& rep)
        {
            // Decode url to path.
            std::string request_path;
            if (!url_decode(req.uri, request_path))
            {
                rep = reply::stock_reply(reply::bad_request);
                return;
            }
            std::cout << "request_url: " + request_path + '\n';

            // Request path must be absolute and not contain "..".
            if (request_path.empty() || request_path[0] != '/'
                || request_path.find("..") != std::string::npos)
            {
                rep = reply::stock_reply(reply::bad_request);
                return;
            }

            // If path ends in slash (i.e. is a directory) then add "index.html".
            if (request_path[request_path.size() - 1] == '/')
            {
                request_path += "index.html";
            }

            // Determine the file extension.
            std::size_t last_slash_pos = request_path.find_last_of("/");
            std::size_t last_dot_pos = request_path.find_last_of(".");
            std::string extension;
            if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos)
            {
                extension = request_path.substr(last_dot_pos + 1);
            }

            // Open the file to send back.
            std::string full_path = doc_root_ + request_path;
            std::cout << "full path to return file: " + full_path + '\n';
            std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
            if (!is)
            {
                rep = reply::stock_reply(reply::not_found);
                return;
            }

            // Fill out the reply to be sent to the client.
            rep.status = reply::ok;
            char buf[512];
            while (is.read(buf, sizeof(buf)).gcount() > 0)
                rep.content.append(buf, is.gcount());
            rep.headers.resize(2);
            rep.headers[0].name = "Content-Length";
            rep.headers[0].value = std::to_string(rep.content.size());
            rep.headers[1].name = "Content-Type";
            rep.headers[1].value = mime_types::extension_to_type(extension);
        }

        void request_handler::handle_request(const request& req, reply& rep, database_manager& db_manager)
        {
            // Decode url to path.
            std::string request_path;
            if (!url_decode(req.uri, request_path))
            {
                rep = reply::stock_reply(reply::bad_request);
                return;
            }
            std::cout << "request_url: " + request_path + '\n';

            // Request path must be absolute and not contain "..".
            if (request_path.empty() || request_path[0] != '/'
                || request_path.find("..") != std::string::npos)
            {
                rep = reply::stock_reply(reply::bad_request);
                return;
            }

            if (request_path == "/movies") {
                rep.status = reply::ok;

                auto buf = db_manager.get_json_recommends_test(std::vector<int>{0, 1, 2});
                std::cout << "return json: " << buf << '\n';
                rep.content.append(to_string(buf));

//                auto buf = db_manager.get_json_from_query_test();
//                rep.content.append(buf);

                rep.headers.resize(2);
                rep.headers[0].name = "Content-Length";
                rep.headers[0].value = std::to_string(rep.content.size());
                rep.headers[1].name = "Content-Type";
                rep.headers[1].value = "application/json";

                return;
            }

            // If path ends in slash (i.e. is a directory) then add "index.html".
            if (request_path[request_path.size() - 1] == '/')
            {
                request_path += "index.html";
            }

            // Determine the file extension.
            std::size_t last_slash_pos = request_path.find_last_of("/");
            std::size_t last_dot_pos = request_path.find_last_of(".");
            std::string extension;
            if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos)
            {
                extension = request_path.substr(last_dot_pos + 1);
            }

            // Open the file to send back.
            std::string full_path = doc_root_ + request_path;
            std::cout << "full path to return file: " + full_path + '\n';
            std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
            if (!is)
            {
                rep = reply::stock_reply(reply::not_found);
                return;
            }

            // Fill out the reply to be sent to the client.
            rep.status = reply::ok;
            char buf[512];
            while (is.read(buf, sizeof(buf)).gcount() > 0)
                rep.content.append(buf, is.gcount());
            rep.headers.resize(2);
            rep.headers[0].name = "Content-Length";
            rep.headers[0].value = std::to_string(rep.content.size());
            rep.headers[1].name = "Content-Type";
            rep.headers[1].value = mime_types::extension_to_type(extension);
        }

        bool request_handler::url_decode(const std::string& in, std::string& out)
        {
            out.clear();
            out.reserve(in.size());
            for (std::size_t i = 0; i < in.size(); ++i)
            {
                if (in[i] == '%')
                {
                    if (i + 3 <= in.size())
                    {
                        int value = 0;
                        std::istringstream is(in.substr(i + 1, 2));
                        if (is >> std::hex >> value)
                        {
                            out += static_cast<char>(value);
                            i += 2;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else
                    {
                        return false;
                    }
                }
                else if (in[i] == '+')
                {
                    out += ' ';
                }
                else
                {
                    out += in[i];
                }
            }
            return true;
        }

    } // namespace server
} // namespace http


// _________________________________________________________________


#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>

using boost::asio::ip::tcp;

class session
  : public std::enable_shared_from_this<session>
{
public:
  session(tcp::socket&& socket)
    : socket_(std::move(socket))
  {
  }

  void start()
  {
    do_read();
  }

private:
  void do_read()
  {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            do_write(length);
          }
        });
  }

  void do_write(std::size_t length)
  {
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            do_read();
          }
        });
  }

  tcp::socket socket_;
  enum { max_length = 1024 };
  char data_[max_length];
};

class server
{
public:
  server(boost::asio::io_service& io_context, short port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)),
      socket_(io_context)
  {
    do_accept();
  }

private:
  void do_accept()
  {
    acceptor_.async_accept(socket_,
        [this](const boost::system::error_code& ec)
        {
          if (!ec)
          {
            session(std::move(socket_));
            }

          do_accept();
        });
  }

  tcp::acceptor acceptor_;  
  tcp::socket socket_;
};

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: async_tcp_echo_server <port>\n";
      return 1;
    }

    boost::asio::io_service io_context;

    server s(io_context, std::atoi(argv[1]));

    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}


// _________________________________________________________________


#include "connection_manager.hpp"

namespace http {
    namespace server {

        connection_manager::connection_manager()
        {
        }

        void connection_manager::start(connection_ptr c)
        {
            connections_.insert(c);
            c->start();
        }

        void connection_manager::stop(connection_ptr c)
        {
            connections_.erase(c);
            c->stop();
        }

        void connection_manager::stop_all()
        {
            for (auto c: connections_)
                c->stop();
            connections_.clear();
        }

    } // namespace server
} // namespace http