#include "builder.hpp"

#include <cmath>
#include <exception>
#include <fstream>
#include <iostream>
#include <limits>

#include "pdf_link_obj.hpp"
#include "pdf_text_obj.hpp"

std::string Builder::FileToString(std::ifstream &file_stream) {
  char ch;
  std::string str;

  while (true) {
    file_stream.get(ch);
    if (file_stream.eof()) break;
    if (ch == '\t') continue;
    str.push_back(ch);
  }

  return str;
};

std::vector<int> getAllIndexes(const std::string &str,
                               const std::string &sub_str) {
  std::vector<int> idxs;
  if (str.empty()) return idxs;
  idxs.clear();

  size_t idx = 0;

  while ((idx = str.find(sub_str, idx)) != std::string::npos)
    idxs.push_back(idx), ++idx;

  return idxs;
}

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
};

std::vector<PdfObject *> Builder::BuildTree() {
  std::string source_file_;
  std::string template_file_;

  // buffering source file
  std::ifstream source_in(source_file_name_);
  if (!source_in.is_open()) {
    std::cerr << "Source file do not exists" << std::endl;
    throw "Source file do not exists";
  }
  source_file_ = FileToString(source_in);
  source_in.close();

  // buffering template file
  std::ifstream template_in(template_file_name_);
  if (!template_in.is_open()) {
    std::cerr << "Template file do not exists" << std::endl;
    throw "Template file do not exists";
  }
  template_file_ = FileToString(template_in);
  template_in.close();

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  std::string start_substring;
  std::string end_substring;
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

  std::vector<int> start_indexes = getAllIndexes(source_file_, template_start);
  std::vector<int> end_indexes = getAllIndexes(source_file_, template_end);

  std::vector<PdfObject *> obj_tree;
  ///////////////
  //  std::cout << start_indexes.size() << " " << end_indexes.size() <<
  //  std::endl;
  long long content_word_argument = std::numeric_limits<long long>::max();
  if ((content_word_end - content_word_start) > 10) {
    content_word_argument = std::stoi(template_file_.substr(
        content_word_start + 9, content_word_end - content_word_start - 10));
  } else {
    content_word_argument = std::min(start_indexes.size(), end_indexes.size());
  }
  for (int i = 0; i < content_word_argument; i++) {
    std::string substr = source_file_.substr(start_indexes[i],
                                             end_indexes[i] - start_indexes[i]);

    DeletTagsExceptLinks(substr);

    std::string text_buffer, link_buffer;
    int last_start = 0;
    bool is_link = 0;
    for (int i = 0, size = substr.size(); i < size; i++) {
      if (substr[i] == '<' && !is_link) {
        is_link = 1;
        obj_tree.push_back(
            new PdfTextObj(substr.substr(last_start, i - last_start)));
        last_start = i;
      }
      if (substr[i] == '>' && substr[i - 1] == 'a' && is_link) {
        is_link = 0;
        obj_tree.push_back(
            new PdfLinkObj(substr.substr(last_start, i + 1 - last_start)));
        last_start = i + 1;
      }
    }
  }
  //////////
  return obj_tree;
};