#pragma once
#include <iostream>
#include <fstream>
#include <vector>

namespace Html
{
    class GetHtml
    {
    public:
    GetHtml() = default;
    GetHtml(const std::string & filename, const std::string & address, 
            const std::string & action);
    GetHtml(const GetHtml& source_html);
    GetHtml& operator=(const GetHtml& source_html);
    
    void SendRequestAndGetResponse();
    void WriteResponseToFile();

    std::string& GetStrResponse();
    
    std::vector <std::pair<std::string, std::string>>& GetLinksToTitles();

    void CreateSubPage(const int & subpages_number) const;

    private:
    static size_t GetResponsetoString(void* contents, size_t size, size_t nmemb, void* userp);

    std::ofstream output_stream_;
    std::string filename_;
    std::string str_response_;
    std::string host_;
    std::string target_;
    std::vector <std::pair<std::string, std::string>> links_to_titles_;
   // static const std::string WWW;
   // static const std::string TARGET;
    };


    namespace Web {
        static const std::string WWW = "www";
        static const std::string TARGET = "<div class=\"lessontable-row-title\">";
        static const std::string PROTOCOL = "https";
        static const std::string SLASH = "/";
        static const std::string BSLASH = "\\";
        static const std::string QUOT = "\"";
        static const std::string EXTEN = ".html";
        static const std::string PATH = "project/html/";
    }
}