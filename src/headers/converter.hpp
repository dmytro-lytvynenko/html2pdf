
#ifndef _CONVERTER_
#define _CONVERTER_

#include <fstream>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include <iostream>
#include <fstream>
extern "C"
{
#include "hpdf.h"
}

class Converter
{
public:
        Converter(const std::string &address, const std::string &action);

        void render();

        ~Converter();

private:
        // I/O context necessary for all I/O operations
        boost::asio::io_context ioc;
        // Tcp soket used for connection
        boost::asio::ip::tcp::socket socket;
        // Resolver for defenitions of endpoints
        boost::asio::ip::tcp::resolver resolver;

        std::ofstream out;
        std::string host;
        std::string target;
};

#endif