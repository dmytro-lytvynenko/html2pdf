#pragma once
#include <iostream>
#include <fstream>
#include <map>

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
    
    std::map<std::string, std::string>& GetLinksToTitles();

    void CreateSubPage(const int & subpages_number) const;

    private:
    static size_t GetResponsetoString(void* contents, size_t size, size_t nmemb, void* userp);

    std::ofstream output_stream_;
    std::string filename_;
    std::string str_response_;
    std::string host_;
    std::string target_;
    std::map<std::string, std::string> links_to_titles_;
    };
}