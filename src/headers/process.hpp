#pragma once
#include <fstream>
#include <boost/beast.hpp>
#include <boost/asio.hpp>

namespace http = boost::beast::http;
using tcp = boost::asio::ip::tcp;


class Process
{
public:
    Process(const std::string & address, const std::string & action);
    
    void send();
    void read();

    ~Process();
private:
    //I/O контекст, необходимый для всех I/O операций
    boost::asio::io_context ioc;
    // Tcp сокет, использующейся для соединения
    tcp::socket socket;
    // Resolver для определения endpoint'ов
    tcp::resolver resolver;
    
    std::ofstream out;
    std::string host;
    std::string target;
};