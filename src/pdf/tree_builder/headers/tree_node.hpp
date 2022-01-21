
#ifndef TREENODE_H_
#define TREENODE_H_

#include "writer.hpp"

namespace PDF {

class TreeNode {
 public:
  virtual void Render(Writer&) = 0;
  virtual ~TreeNode(){};
};

}  // namespace PDF

#endif