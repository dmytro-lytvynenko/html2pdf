
#ifndef CONVERTER_H_
#define CONVERTER_H_

#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "tree_link_node.hpp"
#include "tree_text_node.hpp"
extern "C" {
#include "hpdf.h"
}

namespace PDF {
extern jmp_buf env;

class Converter {
 public:
  Converter(const std::string &source_filename,
            std::vector<TreeNode *> obj_tree);

  void Render();

  ~Converter(){};

 private:
  int max_y_, max_x_;
  std::vector<TreeNode *> obj_tree_;
  std::string source_filename_;
  const std::string output_filename_ = "./project/converted.pdf";
};

}  // namespace PDF

#endif