#pragma once
#include <fstream>
#include <boost/beast.hpp>
#include <boost/asio.hpp>

class Process
{
public:
    Process(const std::string & address, const std::string & action);
    
    void send();
    void read();

    ~Process();
private:
    //I/O context necessary for all I/O operations
    boost::asio::io_context ioc;
    // Tcp soket used for connection
    boost::asio::ip::tcp::socket socket;
    // Resolver for defenitions of endpoints
    boost::asio::ip::tcp::resolver resolver;
    
    std::ofstream out;
    std::string host;
    std::string target;
};