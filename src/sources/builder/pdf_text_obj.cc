#include "pdf_text_obj.hpp"

#include <algorithm>
#include <iostream>

void PdfTextObj::Render(Writer &writer) {
  std::string buffer = text_;
  char sep = '\n';
  std::vector<std::string> lines;
  for (size_t p = 0, q = 0; p != buffer.npos; p = q)
    lines.push_back(buffer.substr(
        p + (p != 0), (q = buffer.find(sep, p + 1)) - p - (p != 0)));

  for (auto it : lines) {
    std::replace(it.begin(), it.end(), '\n', ' ');
    std::replace(it.begin(), it.end(), '\0', ' ');
    writer.PrintLine(it);
  }
};