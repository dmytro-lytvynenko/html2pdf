
#ifndef WRITER_H_
#define WRITER_H_

#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fstream>
#include <iostream>
#include <vector>

extern "C" {
#include "hpdf.h"
}

struct Writer {
  Writer() : current_x(15), current_y((700) * 15){};

  HPDF_Font font;
  HPDF_Page index_page;
  HPDF_Rect rect;
  HPDF_Point tp;
  int current_x;
  int current_y;

  void PrintLine(std::string text) {
    /* begining writing */
    HPDF_Page_BeginText(index_page);

    HPDF_Page_SetFontAndSize(index_page, font, 5);
    HPDF_Page_MoveTextPos(index_page, current_x, current_y);
    HPDF_Page_ShowText(index_page, text.c_str());

    HPDF_Page_EndText(index_page);

    current_y -= 5;
  };
  void PrintLink(std::string text, std::string link) {
    /* Create Link-Annotation object on index page. */
    HPDF_Page_BeginText(index_page);
    HPDF_Page_SetFontAndSize(index_page, font, 5);
    HPDF_Page_MoveTextPos(index_page, current_x, current_y);
    HPDF_Page_SetTextLeading(index_page, 23);

    /* URI link */
    tp = HPDF_Page_GetCurrentTextPos(index_page);

    HPDF_Page_ShowText(index_page, text.c_str());

    rect.left = tp.x - 2;
    rect.bottom = tp.y - 2;
    rect.right = HPDF_Page_GetCurrentTextPos(index_page).x + 4;
    rect.top = tp.y + 6;

    HPDF_Page_CreateURILinkAnnot(index_page, rect, link.c_str());

    HPDF_Page_EndText(index_page);

    current_y -= 8;
  };
};

#endif