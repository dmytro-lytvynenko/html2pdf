
#ifndef TREELINKNODE_H_
#define TREELINKNODE_H_

#include <string>

#include "tree_node.hpp"

namespace PDF {

class TreeLinkNode : public TreeNode {
  std::string text_;
  std::string link_;

 public:
  TreeLinkNode(std::string text, std::string link) : text_(text), link_(link){};
  TreeLinkNode(std::string raw_html);
  void SetText(std::string text) { text_ = text; };
  std::string &GetText() { return text_; };
  void SetLink(std::string link) { link_ = link; };
  std::string &GetLink() { return link_; };

  virtual void Render(Writer &writer);
};

}  // namespace PDF

#endif