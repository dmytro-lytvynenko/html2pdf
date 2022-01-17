#include <get_html.hpp>
#include <sys/stat.h>
#include "converter.hpp"

int main() 
{   
    mkdir("project",0777);
    mkdir("project/html",0777);
    GetHtml MainHtml("learncpp", "https://www.learncpp.com", "/");

    MainHtml.SendRequestAndGetResponse();

    MainHtml.FindLinks(5);
    MainHtml.ChangeLink(5);

    MainHtml.WriteResponseToFile();

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