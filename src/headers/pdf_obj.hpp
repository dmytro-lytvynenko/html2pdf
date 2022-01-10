
#ifndef PDF_OBJ_H_
#define PDF_OBJ_H_

#include "writer.hpp"

class PdfObject {
 public:
  virtual void Render(Writer&) = 0;
  virtual ~PdfObject(){};
};

#endif