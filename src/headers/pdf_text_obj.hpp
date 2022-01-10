#ifndef PDF_TEXT_OBJ_H_
#define PDF_TEXT_OBJ_H_

#include <string>

#include "pdf_obj.hpp"
#include "writer.hpp"

class PdfTextObj : public PdfObject {
  std::string text_;

 public:
  PdfTextObj(std::string text) : text_(text){};
  void SetText(std::string text) { text_ = text; };
  std::string& GetText() { return text_; };

  virtual void Render(Writer& writer);
};

#endif