#include <process.hpp>

#include "builder.hpp"
#include "converter.hpp"

int main() {
  Process GetHtml("https://www.learncpp.com", "/");
  GetHtml.Send();
  GetHtml.SetTarget("/cpp-tutorial/introduction-to-these-tutorials/");
  GetHtml.Send();
  GetHtml.ChangeFirstLink();
  GetHtml.Read();

  Builder builder;
  std::vector<PdfObject *> obj_tree;
  try {
    obj_tree = builder.BuildTree();
  } catch (...) {
    return 1;
  }

  Converter converter("../Docs/ulinks", obj_tree);
  try {
    converter.Render();
  } catch (...) {
    return 1;
  }

  return 0;
}

// include curl to process.cpp