#include <process.hpp>

int main() 
{   
    Process getHtml("www.example.com", "/echo?input=test");

    getHtml.send();
    getHtml.read();

    return 0;
}