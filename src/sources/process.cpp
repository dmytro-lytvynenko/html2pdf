#include <process.hpp>
#define CURL_STATICLIB
#include <curl/curl.h>

Process::Process(const std::string & fileName, const std::string & address, const std::string & action)
{
    filename_ = fileName;
    host_ = address;
    target_ = action;
}

// void Process::SetTarget(const std::string & target)
// {
//     target_=target;
// }

void Process::FindLinks(const int & idx) {
    int i=0;
    int curr=0;
    std::string link;
    while (i!=idx) {
        curr = str_response_.find("<div class=\"lessontable-row-title\">",curr);
        curr = str_response_.find("www",++curr);
        curr = str_response_.find("/",++curr);

        int begin = curr;

        int end = str_response_.find("\"",curr);

        link = GetString(begin,end);

        links_to_titles_[link] = "";

        i++;
    }

}

// std::string Process::GetTitle(const int & idx) {
//     return titles_[idx];
// }

// std::string Process::GetLink(const int & idx) {
//     return links_[idx];
// }

void Process::ChangeLink(const int & idx){
    int i=0;
    auto it = links_to_titles_.begin();
    int curr=0;
    std::string link;
    while (i!=idx) {
        curr = str_response_.find("<div class=\"lessontable-row-title\">",curr);
        curr = str_response_.find("https",++curr);

        int begin = curr;
        int end = str_response_.find("\"",begin) - 1;

        curr = str_response_.find("www", curr);
        curr = str_response_.find("/",++curr);
        curr = str_response_.find("/",++curr);

        link = GetString(++curr,end);

        it->second = link;

        str_response_.replace(begin,end-begin+1,link+".html");

        i++;
        it++;
    }

    EraseTag("base");
}

std::string Process::GetString(int begin, const int & end){
    std::string str;
    while (begin!=end)
        str+=str_response_[begin++];

    return str;
}

void Process::CreateSubPage(const int & idx){
    int i=0;
    auto it = links_to_titles_.begin();
    while (i!=idx){
        Process SubPage(it->second,host_,it->first);
        
        SubPage.Send();
        SubPage.Read();

        i++;
        it++;
    }
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
    try
    {
        out_.open("project/html/"+filename_+".html");
        
        try
        {
            out_ << str_response_ << std::endl;
        }
        catch(...)
        {
            std::cout << "Failed writing to html file" << std::endl;
        }

        out_.close();
    }
    catch(...)
    {
        std::cout << "Failed work with html files" << std::endl;
    }
}