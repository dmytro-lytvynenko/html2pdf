#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include <iostream>
#include <fstream>
extern "C"
{
#include "hpdf.h"
}

jmp_buf env;

#ifdef HPDF_DLL
void __stdcall
#else
void
#endif
    error_handler(HPDF_STATUS error_no,
                  HPDF_STATUS detail_no,
                  void *user_data)
{
        printf("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no,
               (HPDF_UINT)detail_no);
        longjmp(env, 1);
}

void print_page(HPDF_Page page, HPDF_Font font, int page_num)
{
        char buf[50];

        HPDF_Page_SetWidth(page, 200);
        HPDF_Page_SetHeight(page, 200);

        HPDF_Page_SetFontAndSize(page, font, 20);

        HPDF_Page_BeginText(page);
        HPDF_Page_MoveTextPos(page, 50, 150);
#ifdef __WIN32__
        _snprintf(buf, 50, "Page:%d", page_num);
#else
        snprintf(buf, 50, "Page:%d", page_num);
#endif
        HPDF_Page_ShowText(page, buf);
        HPDF_Page_EndText(page);
}

int main(int argc, char **argv)
{
        std::string line;
        std::string buffer;

        std::ifstream in("Docs/ulinks");
        if (!in.is_open())
        {
                std::cerr << "File Docs/ulinks do not exists" << std::endl;
                return 0;
        }

        while (getline(in, line))
        {
                buffer += line;
                std::cout
                    << line << std::endl;
        }
        in.close();

        std::string link = buffer.substr(buffer.size() - 44, 45); // link length=44
        buffer = buffer.substr(0, buffer.size() - 44);

        HPDF_Doc pdf;
        HPDF_Font font;
        HPDF_Page index_page;
        HPDF_Page page[9];
        HPDF_Destination dst;
        char fname[256];
        HPDF_Rect rect;
        HPDF_Point tp;
        HPDF_Annotation annot;
        HPDF_UINT i;
        const char *uri = link.c_str();

        strcpy(fname, argv[0]);
        strcat(fname, ".pdf");

        pdf = HPDF_New(error_handler, NULL);
        if (!pdf)
        {
                printf("error: cannot create PdfDoc object\n");
                return 1;
        }

        if (setjmp(env))
        {
                HPDF_Free(pdf);
                return 1;
        }

        /* create default-font */
        font = HPDF_GetFont(pdf, "Helvetica", NULL);

        /* create index page */
        index_page = HPDF_AddPage(pdf);
        HPDF_Page_SetWidth(index_page, 300);
        HPDF_Page_SetHeight(index_page, 220);

        /* Add 7 pages to the document. */
        // for (i = 0; i < 7; i++)
        // {
        //         page[i] = HPDF_AddPage(pdf);
        //         print_page(page[i], font, i + 1);
        // }

        HPDF_Page_BeginText(index_page);
        HPDF_Page_SetFontAndSize(index_page, font, 10);
        HPDF_Page_MoveTextPos(index_page, 15, 200);
        HPDF_Page_ShowText(index_page, buffer.c_str());
        HPDF_Page_EndText(index_page);

        /*
         * Create Link-Annotation object on index page.
         */
        HPDF_Page_BeginText(index_page);
        HPDF_Page_SetFontAndSize(index_page, font, 8);
        HPDF_Page_MoveTextPos(index_page, 20, 180);
        HPDF_Page_SetTextLeading(index_page, 23);

        // /* page1 (HPDF_ANNOT_NO_HIGHTLIGHT) */
        // tp = HPDF_Page_GetCurrentTextPos(index_page);

        // HPDF_Page_ShowText(index_page, "Jump to Page1 (HilightMode=HPDF_ANNOT_NO_HIGHTLIGHT)");
        // rect.left = tp.x - 4;
        // rect.bottom = tp.y - 4;
        // rect.right = HPDF_Page_GetCurrentTextPos(index_page).x + 4;
        // rect.top = tp.y + 10;

        // HPDF_Page_MoveToNextLine(index_page);

        // dst = HPDF_Page_CreateDestination(page[0]);

        // annot = HPDF_Page_CreateLinkAnnot(index_page, rect, dst);

        // HPDF_LinkAnnot_SetHighlightMode(annot, HPDF_ANNOT_NO_HIGHTLIGHT);

        /* URI link */
        tp = HPDF_Page_GetCurrentTextPos(index_page);

        HPDF_Page_ShowText(index_page, "URI (");
        HPDF_Page_ShowText(index_page, uri);
        HPDF_Page_ShowText(index_page, ")");

        rect.left = tp.x - 4;
        rect.bottom = tp.y - 4;
        rect.right = HPDF_Page_GetCurrentTextPos(index_page).x + 4;
        rect.top = tp.y + 10;

        HPDF_Page_CreateURILinkAnnot(index_page, rect, uri);

        HPDF_Page_EndText(index_page);

        /* save the document to a file */
        HPDF_SaveToFile(pdf, fname);

        /* clean up */
        HPDF_Free(pdf);

        return 0;
}
