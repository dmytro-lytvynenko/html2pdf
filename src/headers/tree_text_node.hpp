#ifndef TREETEXTNODE_H_
#define TREETEXTNODE_H_

#include <string>

#include "tree_node.hpp"
#include "writer.hpp"

namespace PDF {

class TreeTextNode : public TreeNode {
  std::string text_;

 public:
  TreeTextNode(std::string text) : text_(text){};
  void SetText(std::string text) { text_ = text; };
  std::string& GetText() { return text_; };

  virtual void Render(Writer& writer);
};

}  // namespace PDF

#endif