#include <process.hpp>
#include <sys/stat.h>

#include "builder.hpp"
#include "converter.hpp"

int main() {
    mkdir("project",0777);
    mkdir("project/html",0777);
    Process MainHtml("learncpp", "https://www.learncpp.com", "/");

    MainHtml.Send();

    MainHtml.FindLinks(5);
    MainHtml.ChangeLink(5);

    MainHtml.Read();

    MainHtml.CreateSubPage(5);


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