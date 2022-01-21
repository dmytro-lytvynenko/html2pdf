#ifndef TREEBUILDER_H_
#define TREEBUILDER_H_

#include <string>
#include <vector>

#include "tree_link_node.hpp"
#include "tree_text_node.hpp"

namespace PDF {

class TreeBuilder {
  /*      Hardcode!     */
  std::string template_file_name_ = "../learncpp.template";
  std::string source_file_name_ = "./project/html/learncpp.html";

 public:
  std::vector<TreeNode *> BuildTree();
};

}  // namespace PDF

#endif
