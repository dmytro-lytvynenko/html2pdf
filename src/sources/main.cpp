#include <process.hpp>

int main() 
{   
    Process GetHtml("https://www.learncpp.com", "/");

    GetHtml.Send();
    GetHtml.Read();

    return 0;
}

//include curl to process.cpp