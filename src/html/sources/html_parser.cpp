#include "html_parser.hpp"

Html::HtmlParser::HtmlParser(Html::GetHtml & html_page)
{ 
    html_page_ = &html_page;
}

void Html::HtmlParser::FindLinks(const int & links_number) {
    int curr = 0;
    int count=0;
    std::string link;
    while (count!=links_number) {
        curr = html_page_->GetStrResponse().find("<div class=\"lessontable-row-title\">",curr);
        curr = html_page_->GetStrResponse().find("www",++curr);
        curr = html_page_->GetStrResponse().find("/",++curr);

        int begin = curr;

        int end = html_page_->GetStrResponse().find("\"",curr);

        link = GetString(begin,end);

        html_page_->GetLinksToTitles().insert(std::pair<std::string, std::string>(link, ""));

        count++;
    }
}

void Html::HtmlParser::ChangeLink(const int & links_number){
    auto it = html_page_->GetLinksToTitles().begin();
    int curr = 0;
    int count=0;
    std::string link;
    while (count!=links_number) {
        curr = html_page_->GetStrResponse().find("<div class=\"lessontable-row-title\">",curr);
        curr = html_page_->GetStrResponse().find("https",++curr);
        
        int begin = curr;
        int end = html_page_->GetStrResponse().find("\"",begin) - 1;

        curr = html_page_->GetStrResponse().find("www", curr);
        curr = html_page_->GetStrResponse().find("/",++curr);
        curr = html_page_->GetStrResponse().find("/",++curr);

        link = GetString(++curr,end);

        it->second = link;

        html_page_->GetStrResponse().replace(begin,end-begin+1,link+".html");

        count++;
        it++;
    }
    EraseTag("base");
}

std::string Html::HtmlParser::GetString(int & begin, const int & end)
{ 
    try
    {
        return html_page_->GetStrResponse().substr(begin, end - begin);
    }
    catch(...)
    {
        std::cout << "Error while getting link or title! " 
                  << "Response emptyness = " << html_page_->GetStrResponse().empty() << std::endl; 
        return "";
    }
}

void Html::HtmlParser::EraseTag(std::string tag)
{
    tag='<'+tag;
    while(html_page_->GetStrResponse().find(tag)!=std::string::npos)
    {
        int begin=html_page_->GetStrResponse().find(tag);
        int end=begin;
        while(html_page_->GetStrResponse()[end]!='>')
        {
            end++;
        }
        html_page_->GetStrResponse().erase(begin,end-begin+1);
    }
}