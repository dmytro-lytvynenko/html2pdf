#include <process.hpp>

Process::Process(const std::string & address, const std::string & action) 
            : resolver(ioc), socket(ioc)
            {
                out.open("localversion.html");

                host = address;
                target = action;
            }

void Process::send()
{
    // Resolve address and create connection
    boost::asio::connect(socket, resolver.resolve(host, "80"));

    // Then create http request
    boost::beast::http::request<boost::beast::http::string_body> req(boost::beast::http::verb::get, target, 11);
    // HTTP header fields
    req.set(boost::beast::http::field::host, host);
    req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    
    // Send request
    boost::beast::http::write(socket, req);
}

void Process::read()
{
    boost::beast::flat_buffer buffer;
    boost::beast::http::response<boost::beast::http::dynamic_body> res;
    boost::beast::http::read(socket, buffer, res);
    
    // write correct response to local file
    out << boost::beast::buffers_to_string(res.body().data()) << std::endl;
}

Process::~Process()
{
    // Close connection
    socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    out.close();
}