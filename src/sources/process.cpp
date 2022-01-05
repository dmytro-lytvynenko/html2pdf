#include <process.hpp>
#define CURL_STATICLIB
#include <curl/curl.h>

Process::Process(const std::string & address, const std::string & action)
{
    out_.open("learncpp.html");
    host_ = address;
    target_ = action;
}

void Process::SetTarget(const std::string & target)
{
    target_=target;
}

void Process::ChangeFirstLink(){
    int i=str_response_.find(host_+target_);
    str_response_.replace(i,(host_+target_).size(),"#first_link");

    i=str_response_.find("0.1 — Introduction to these tutorials</h1>");
    str_response_.insert(--i," id=\"first_link\"");

    EraseTag("base");

}

void Process::EraseTag(std::string tag){
    tag='<'+tag;
    while(str_response_.find(tag)!=std::string::npos)
    {
    int begin=str_response_.find(tag);
    int end=begin;
    while(str_response_[end]!='>')
    {
        end++;
    }
    str_response_.erase(begin,end-begin+1);
    }
}


size_t Process::GetResponsetoString(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void Process::Send()
{
    CURL* curl;
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, (host_+target_).c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, GetResponsetoString);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str_response_);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
}

void Process::Read()
{
    out_ << str_response_ << std::endl;
}


Process::~Process()
{
    out_.close();
}