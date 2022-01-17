#include <get_html.hpp>
#define CURL_STATICLIB
#include <curl/curl.h>

GetHtml::GetHtml(const std::string & filename, const std::string & address, 
                 const std::string & action)
{
    filename_ = filename;
    host_ = address;
    target_ = action;
}

void GetHtml::FindLinks(const int & links_number) {
    int curr = 0;
    int count=0;
    std::string link;
    while (count!=links_number) {
        curr = str_response_.find("<div class=\"lessontable-row-title\">",curr);
        curr = str_response_.find("www",++curr);
        curr = str_response_.find("/",++curr);

        int begin = curr;

        int end = str_response_.find("\"",curr);

        link = GetString(begin,end);

        links_to_titles_[link] = "";

        count++;
    }
}

void GetHtml::ChangeLink(const int & links_number){
    auto it = links_to_titles_.begin();
    int curr = 0;
    int count=0;
    std::string link;
    while (count!=links_number) {
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

        count++;
        it++;
    }
    
    EraseTag("base");
}

std::string GetHtml::GetString(int & begin, const int & end) const
{ 
    try
    {
        return str_response_.substr(begin, end - begin);
    }
    catch(...)
    {
        std::cout << "Error while getting link or title! " 
                  << "Response emptyness = " << str_response_.empty() << std::endl; 
        return "";
    }
}

void GetHtml::CreateSubPage(const int & subpages_number){
    int count=0;
    auto it = links_to_titles_.begin();
    while (count!=subpages_number){
        GetHtml SubPage(it->second,host_,it->first);

        SubPage.SendRequestAndGetResponse();
        SubPage.WriteResponseToFile();

        count++;
        it++;
    }
}

void GetHtml::EraseTag(std::string tag){
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

size_t GetHtml::GetResponsetoString(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void GetHtml::SendRequestAndGetResponse()
{
    CURL* descriptor = curl_easy_init();
    curl_easy_setopt(descriptor, CURLOPT_URL, (host_+target_).c_str());
    curl_easy_setopt(descriptor, CURLOPT_WRITEFUNCTION, GetResponsetoString);
    curl_easy_setopt(descriptor, CURLOPT_WRITEDATA, &str_response_);
    curl_easy_perform(descriptor);
    curl_easy_cleanup(descriptor);
}

void GetHtml::WriteResponseToFile()
{
    try
    {
        output_stream_.open("project/html/"+filename_+".html");
        
        try
        {
            output_stream_ << str_response_ << std::endl;
        }
        catch(...)
        {
            std::cout << "Failed writing to html file" << std::endl;
        }

        output_stream_.close();
    }
    catch(...)
    {
        std::cout << "Failed work with html files" << std::endl;
    }
}