#include "tree_builder.hpp"

#include <cmath>
#include <exception>
#include <fstream>
#include <iostream>
#include <limits>

#include "pdf_helper.hpp"
#include "tree_link_node.hpp"
#include "tree_text_node.hpp"

namespace PDF_helper {
void DeletTagsExceptLinks(std::string &str) {
  std::string new_string;

  //
  for (int i = 0, size = str.size() - 1; i < size; i++) {
    if (str[i] == '<' && str[i + 1] == ' ') {
      str.erase(i + 1, 1);
    }
  }

  bool is_tag = 0;  // is it ignored tag
  for (int i = 0, size = str.size(); i < size; i++) {
    if (str[i] != '>' && is_tag) {
      continue;
    }
    if (is_tag && str[i] == '>') {
      is_tag = 0;
      continue;
    }
    if (str[i] == '<' && str[i + 1] != 'a' && str[i + 2] != 'a') {
      is_tag = 1;
      continue;
    }
    new_string.push_back(str[i]);
  }
  str = new_string;
}
}  // namespace PDF_helper

namespace PDF {

std::vector<TreeNode *> TreeBuilder::BuildTree() {
  std::string source_file_;
  std::string template_file_;
  // buffering source file
  std::ifstream source_in(source_file_name_);
  if (!source_in.is_open()) {
    std::cerr << "Source file do not exists" << std::endl;
    throw "Source file do not exists";
  }
  source_file_ = PDF_helper::FileToString(source_in);
  source_in.close();
  // buffering template file
  std::ifstream template_in(template_file_name_);
  if (!template_in.is_open()) {
    std::cerr << "Template file do not exists" << std::endl;
    throw "Template file do not exists";
  }
  template_file_ = PDF_helper::FileToString(template_in);
  template_in.close();

  int content_word_start, content_word_end;
  if (((content_word_start = template_file_.find("\%content")) ==
       std::string::npos) ||
      ((content_word_end = template_file_.find("\%", content_word_start + 1)) ==
       std::string::npos)) {
    std::cerr << "There are no \"%content%\" marker in template file"
              << std::endl;
    throw std::domain_error(
        "There are no \"%content%\" marker in template file");
  }

  std::string template_start = template_file_.substr(0, content_word_start);
  std::string template_end =
      template_file_.substr(content_word_end + 1, template_file_.size() - 1);

  std::vector<int> start_indexes =
      PDF_helper::getAllIndexes(source_file_, template_start);
  std::vector<int> end_indexes =
      PDF_helper::getAllIndexes(source_file_, template_end);

  std::vector<TreeNode *> obj_tree;
  long long content_word_argument;
  if ((content_word_end - content_word_start) > 10) {
    content_word_argument = std::stoi(template_file_.substr(
        content_word_start + 9, content_word_end - content_word_start - 10));
  } else {
    content_word_argument = std::min(start_indexes.size(), end_indexes.size());
  }
  // content_word_argument = std::numeric_limits<long long>::max();

  for (int i = 0; i < content_word_argument; i++) {
    std::string substr = source_file_.substr(start_indexes[i],
                                             end_indexes[i] - start_indexes[i]);

    PDF_helper::DeletTagsExceptLinks(substr);

    int last_start = 0;
    bool is_link = 0;
    for (int j = 0, size = substr.size(); j < size; j++) {
      if (substr[j] == '<' && !is_link) {
        is_link = 1;
        obj_tree.push_back(
            new TreeTextNode(substr.substr(last_start, j - last_start)));
        last_start = j;
      }
      if (substr[j] == '>' && substr[j - 1] == 'a' && is_link) {
        is_link = 0;
        obj_tree.push_back(
            new TreeLinkNode(substr.substr(last_start, j + 1 - last_start)));
        last_start = j + 1;
      }
    }
  }
  return obj_tree;
}

}  // namespace PDF