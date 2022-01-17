
#ifndef PDF_LINK_OBJ_H_
#define PDF_LINK_OBJ_H_

#include <string>

#include "pdf_obj.hpp"

class PdfLinkObj : public PdfObject {
  std::string text_;
  std::string link_;

 public:
  PdfLinkObj(std::string text, std::string link) : text_(text), link_(link){};
  PdfLinkObj(std::string raw_html);
  void SetText(std::string text) { text_ = text; };
  std::string &GetText() { return text_; };
  void SetLink(std::string link) { link_ = link; };
  std::string &GetLink() { return link_; };

  virtual void Render(Writer &writer);
};

#endif