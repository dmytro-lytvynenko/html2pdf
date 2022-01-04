#pragma once
#include <iostream>
#include <fstream>

class Process
{
public:
    Process(const std::string & address, const std::string & action);
    
    void Send();
    void Read();

    void ChangeFirstLink();
    void EraseTag(std::string tag);

    void SetTarget(const std::string & target);
    
    ~Process();
private:
    static size_t GetResponsetoString(void* contents, size_t size, size_t nmemb, void* userp);
    std::ofstream out_;
    std::string str_response_;
    std::string host_;
    std::string target_;
    size_t answer_;
};