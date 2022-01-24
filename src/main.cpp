#include <sys/stat.h>

#include "get_html.hpp"
#include "html_parser.hpp"
#include "converter.hpp"
#include "tree_builder.hpp"


int main(){
  mkdir("project",0777);
  mkdir("project/html",0777);
  Html::GetHtml MainHtml("learncpp", "https://www.learncpp.com", "/");

  MainHtml.SendRequestAndGetResponse();

  Html::HtmlParser ParseMainHtml(MainHtml);

  ParseMainHtml.FindLinks(5);
  ParseMainHtml.ChangeLink(5);

  MainHtml.WriteResponseToFile();

  MainHtml.CreateSubPage(5);


  PDF::TreeBuilder TreeBuilder;
  std::vector<PDF::TreeNode *> obj_tree;
  try {
    obj_tree = TreeBuilder.BuildTree();
  } catch (...) {
    return 1;
  }

  PDF::Converter converter("./project/html/learncpp.html", obj_tree);
  try {
    converter.Render();
  } catch (...) {
    return 1;
  }

  return 0;
}

// include curl to process.cpp