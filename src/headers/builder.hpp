#ifndef BUILDER_H_
#define BUILDER_H_

#include <string>
#include <vector>

#include "pdf_link_obj.hpp"
#include "pdf_text_obj.hpp"

class Builder {
  /*      Hardcode!     */
  std::string template_file_name_ = "../learncpp.template";
  std::string source_file_name_ = "project/html/learncpp.html";
  std::string FileToString(std::ifstream &file_stream);

 public:
  std::vector<PdfObject *> BuildTree();
};
#endif
