#pragma once
#include <iostream>
#include <fstream>
#include <map>

class GetHtml
{
public:
    GetHtml(const std::string & filename, const std::string & address, 
            const std::string & action);
    
    void SendRequestAndGetResponse();
    void WriteResponseToFile();

    void ChangeLink(const int & links_number);
    void EraseTag(std::string tag);

    void FindLinks(const int & links_number);

    void CreateSubPage(const int & subpages_number);

    std::string GetString(int & begin, const int & end) const;

private:
    static size_t GetResponsetoString(void* contents, size_t size, size_t nmemb, void* userp);

    std::ofstream output_stream_;
    std::string filename_;
    std::string str_response_;
    std::string host_;
    std::string target_;
    std::map <std::string, std::string> links_to_titles_;
};