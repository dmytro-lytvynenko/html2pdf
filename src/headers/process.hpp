#pragma once
#include <iostream>
#include <fstream>
#include <map>

class Process
{
public:
    Process(const std::string & fileName, const std::string & address, const std::string & action);
    
    void Send();
    void Read();

    void ChangeLink(const int & idx);
    void EraseTag(std::string tag);

    //void SetTarget(const std::string & target);

    void FindLinks(const int & idx);

    void CreateSubPage(const int & idx);

    // std::string GetTitle(const int & idx);
    // std::string GetLink(const int & idx);

    std::string GetString(int begin, const int & end);

private:
    static size_t GetResponsetoString(void* contents, size_t size, size_t nmemb, void* userp);
    std::ofstream out_;
    std::string filename_;
    std::string str_response_;
    std::string host_;
    std::string target_;
    std::map <std::string, std::string> links_to_titles_;
    size_t answer_;
};