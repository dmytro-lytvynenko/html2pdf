#include "pdf_helper.hpp"

#include <fstream>

namespace PDF_helper {

std::string FileToString(std::ifstream &file_stream) {
  char ch;
  std::string str;

  while (true) {
    file_stream.get(ch);
    if (file_stream.eof()) break;
    // if (ch == '\n')
    //         ch = ' ';
    str.append(1, ch);
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

}  // namespace PDF_helper