#include <process.hpp>
#include "converter.hpp"

int main() 
{   
    Process GetHtml("https://www.learncpp.com", "/");

    GetHtml.Send();

    GetHtml.SetTarget("/cpp-tutorial/introduction-to-these-tutorials/");

    GetHtml.Send();

    GetHtml.ChangeFirstLink();

    GetHtml.Read();

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

//include curl to process.cpp