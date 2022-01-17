#include "pdf_link_obj.hpp"

#include <algorithm>
#include <iostream>

PdfLinkObj::PdfLinkObj(std::string raw_html) {
  int link_index = raw_html.find("href=\"");
  int text_start = raw_html.find(">");
  int text_end = raw_html.find("</a>");

  text_ = raw_html.substr(text_start + 1, text_end - text_start - 1);
  for (int i = link_index + 6; raw_html[i] != '\"'; i++) {
    link_.push_back(raw_html[i]);
  }
};

void PdfLinkObj::Render(Writer& writer) {
  std::replace(text_.begin(), text_.end(), '\n', ' ');
  writer.PrintLink(text_, link_);
};