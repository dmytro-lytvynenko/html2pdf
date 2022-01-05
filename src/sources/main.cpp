#include <process.hpp>

int main() 
{   
    Process GetHtml("https://www.learncpp.com", "/");

    GetHtml.Send();

    GetHtml.SetTarget("/cpp-tutorial/introduction-to-these-tutorials/");

    GetHtml.Send();

    GetHtml.ChangeFirstLink();

    GetHtml.Read();

    return 0;
}

//include curl to process.cpp