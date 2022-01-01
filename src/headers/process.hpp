#pragma once
#define CURL_STATICLIB
#include <fstream>
#include <curl/curl.h>


class Process
{
public:
    Process(const std::string & address, const std::string & action);
    
    void Send();
    void Read();
    

    ~Process();
private:
    static size_t GetResponsetoString(void* contents, size_t size, size_t nmemb, void* userp);
    std::ofstream out;
    std::string str_response;
    std::string host;
    std::string target;
    size_t answer;
};