#ifndef PDFHELPER_H_
#define PDFHELPER_H_

#include <string>
#include <vector>

namespace PDF_helper {

constexpr int page_height = (700) * 15;

std::string FileToString(std::ifstream &file_stream);
std::vector<int> getAllIndexes(const std::string &str,
                               const std::string &sub_str);

}  // namespace PDF_helper

#endif