
#ifndef CONVERTER_H_
#define CONVERTER_H_

#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "pdf_link_obj.hpp"
#include "pdf_text_obj.hpp"
extern "C" {
#include "hpdf.h"
}
extern jmp_buf env;

class Converter {
 public:
  Converter(const std::string &source_filename,
            std::vector<PdfObject *> obj_tree);

  void Render();

  ~Converter(){};

 private:
  int max_y_, max_x_;
  std::vector<PdfObject *> obj_tree_;
  std::string source_filename_;
  const std::string output_filename_ = "converted.pdf";
};

#endif