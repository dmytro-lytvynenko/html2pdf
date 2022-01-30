#include "get_html.hpp"
#define CURL_STATICLIB
#include <curl/curl.h>


Html::GetHtml::GetHtml(const std::string & filename, const std::string & address, 
                 const std::string & action)
{
    filename_ = filename;
    host_ = address;
    target_ = action;
}

Html::GetHtml::GetHtml(const GetHtml& source_html)
    : filename_(source_html.filename_), host_(source_html.host_), target_(source_html.target_),
     str_response_(source_html.str_response_)
{ }

Html::GetHtml& Html::GetHtml::operator=(const GetHtml& source_html)
{
  if (this == &source_html) return *this;

  this->filename_ = source_html.filename_;
  this->host_= source_html.host_;
  this->target_ = source_html.target_;
  this->str_response_ = source_html.str_response_;

  return *this;
}

std::string& Html::GetHtml::GetStrResponse()
{
    return str_response_;
}

std::vector <std::pair<std::string, std::string>>& Html::GetHtml::GetLinksToTitles()
{
    return links_to_titles_;
}

size_t Html::GetHtml::GetResponsetoString(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void Html::GetHtml::CreateSubPage(const int & subpages_number) const{
    int count=0;
    auto it = links_to_titles_.cbegin();
    while (count!=subpages_number){
        GetHtml SubPage(it->second,host_,it->first);

        SubPage.SendRequestAndGetResponse();
        SubPage.WriteResponseToFile();

        count++;
        it++;
    }
}

void Html::GetHtml::SendRequestAndGetResponse()
{
    CURL* descriptor;
    descriptor = curl_easy_init();
    curl_easy_setopt(descriptor, CURLOPT_URL, (host_+target_).c_str());
    curl_easy_setopt(descriptor, CURLOPT_WRITEFUNCTION, GetResponsetoString);
    curl_easy_setopt(descriptor, CURLOPT_WRITEDATA, &str_response_);   
    curl_easy_perform(descriptor);
    curl_easy_cleanup(descriptor);
}

void Html::GetHtml::WriteResponseToFile()
{
    try
    {
        output_stream_.open(Html::Web::PATH+filename_+Html::Web::EXTEN);
        
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