#include <process.hpp>
#include "converter.hpp"

int main()
{
    Process getHtml("www.example.com", "/echo?input=test");

    getHtml.send();
    getHtml.read();

    Converter converter("../Docs/ulinks");
    try
    {
        converter.Render();
    }
    catch (...)
    {
        return 1;
    }

    return 0;
}