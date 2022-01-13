#include <process.hpp>
#include <sys/stat.h>
#include "converter.hpp"

int main() 
{   
    mkdir("project",0777);
    mkdir("project/html",0777);
    Process MainHtml("learncpp", "https://www.learncpp.com", "/");

    MainHtml.Send();

    MainHtml.FindLinks(5);
    MainHtml.ChangeLink(5);

    MainHtml.Read();

    MainHtml.CreateSubPage(5);

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