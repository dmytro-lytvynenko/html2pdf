#include "converter.hpp"

#include "pdf_helper.hpp"

namespace PDF {

jmp_buf env;

/*--------------------------------*/
constexpr int page_width = (150) * 6;
/*--------------------------------*/

Converter::Converter(const std::string &source_filename,
                     std::vector<TreeNode *> obj_tree)
    : source_filename_(source_filename), obj_tree_(obj_tree){};

void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no,
                   void *user_data) {
  printf("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no,
         (HPDF_UINT)detail_no);
  longjmp(env, 1);
}

void Converter::Render() {
  std::ifstream in(source_filename_);
  if (!in.is_open()) {
    std::cerr << "Input HTML file do not exists" << std::endl;
    throw "Input HTML file do not exists";
  }
  // Open an input file

  std::string buffer = PDF_helper::FileToString(in);

  in.close();

  HPDF_Doc pdf;
  HPDF_Font font;
  HPDF_Page index_page;
  HPDF_Destination dst;
  HPDF_Rect rect;
  HPDF_Point tp;
  HPDF_Annotation annot;
  HPDF_UINT i;

  pdf = HPDF_New(error_handler, NULL);
  if (!pdf) {
    std::cerr << "cannot create PdfDoc object" << std::endl;
    throw "cannot create PdfDoc object";
  }

  if (setjmp(env)) {
    std::cerr << "cant setjmp" << std::endl;
    HPDF_Free(pdf);
    throw "cant setjmp";
  }

  /* create default-font */
  font = HPDF_GetFont(pdf, "Helvetica", NULL);

  // split source text by delimiter '\n'
  char sep = '\n';
  std::vector<std::string> lines;
  for (size_t p = 0, q = 0; p != buffer.npos; p = q)
    lines.push_back(buffer.substr(
        p + (p != 0), (q = buffer.find(sep, p + 1)) - p - (p != 0)));

  // find maximum of size of string in vector
  int max_size = 0;
  for (auto it : lines) {
    if (it.size() > max_size) {
      max_size = it.size();
    }
  }

  /* create index page */
  index_page = HPDF_AddPage(pdf);
  HPDF_Page_SetWidth(index_page, page_width);
  HPDF_Page_SetHeight(index_page, PDF_helper::page_height);

  Writer writer;
  writer.index_page = index_page;
  writer.font = font;
  writer.rect = rect;
  writer.tp = tp;

  // print lines in pdf
  for (auto it : obj_tree_) {
    it->Render(writer);
  }

  /* save the document to a file */
  HPDF_SaveToFile(pdf, output_filename_.c_str());

  /* clean up */
  HPDF_Free(pdf);
}

}  // namespace PDF
