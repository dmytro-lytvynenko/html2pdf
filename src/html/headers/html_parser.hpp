#pragma once
#include <iostream>
#include "get_html.hpp"

namespace Html
{
    class HtmlParser
    {
    public:
        HtmlParser(GetHtml & html_page);

        void ChangeLink(const int & links_number);
        void EraseTag(std::string tag);

        void FindLinks(const int & links_number);

        std::string GetString(int & begin, const int & end);

    private:
        GetHtml* html_page_;
    };
}