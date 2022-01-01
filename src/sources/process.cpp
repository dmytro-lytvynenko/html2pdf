#include <process.hpp>
#include <iostream>

Process::Process(const std::string & address, const std::string & action)
            {
                out.open("learncpp.html");
                host = address;
                target = action;
            }

size_t Process::GetResponsetoString(void* contents, size_t size, size_t nmemb, void* userp){
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void Process::Send()
{
    CURL* curl;
    CURLcode response;
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, (host+target).c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, GetResponsetoString);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str_response);
    response = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
}

void Process::Read()
{
    out << str_response << std::endl;
}


Process::~Process()
{
    out.close();
}