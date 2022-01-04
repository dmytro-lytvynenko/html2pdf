#pragma once
#define CURL_STATICLIB
#include <curl/curl.h>
#include <iostream>
#include <fstream>


class Process
{
public:
    Process(const std::string & address, const std::string & action);
    
    void Send();
    void Read();
    
    ~Process();
private:
    static size_t GetResponsetoString(void* contents, size_t size, size_t nmemb, void* userp);
    std::ofstream out_;
    std::string str_response_;
    std::string host_;
    std::string target_;
    size_t answer_;
};