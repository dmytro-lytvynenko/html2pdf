#include <process.hpp>

Process::Process(const std::string & address, const std::string & action)
            {
                out_.open("learncpp.html");
                host_ = address;
                target_ = action;
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