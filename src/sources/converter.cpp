#include "converter.hpp"

jmp_buf env;

void error_handler(HPDF_STATUS error_no,
                   HPDF_STATUS detail_no,
                   void *user_data)
{
        printf("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no,
               (HPDF_UINT)detail_no);
        longjmp(env, 1);
}

std::string FileToString(std::ifstream &file_stream)
{

        char ch;
        std::string str;

        while (true)
        {
                file_stream.get(ch);
                if (file_stream.eof())
                        break;
                // if (ch == '\n')
                //         ch = ' ';
                str.append(1, ch);
        }

        return str;
};

void PrintText(HPDF_Page index_page, HPDF_Font font, std::string text, int x_position, int y_position)
{
        /* begining writing */
        HPDF_Page_BeginText(index_page);

        HPDF_Page_SetFontAndSize(index_page, font, 10);
        HPDF_Page_MoveTextPos(index_page, x_position, y_position);
        HPDF_Page_ShowText(index_page, text.c_str());

        HPDF_Page_EndText(index_page);
};

// ;(
void PrintLink(HPDF_Page index_page,
               HPDF_Font font,
               HPDF_Point tp,
               HPDF_Rect rect,
               std::string text,
               std::string link)
{
        /* Create Link-Annotation object on index page. */
        HPDF_Page_BeginText(index_page);
        HPDF_Page_SetFontAndSize(index_page, font, 8);
        HPDF_Page_MoveTextPos(index_page, 15, 180);
        HPDF_Page_SetTextLeading(index_page, 23);

        /* URI link */
        tp = HPDF_Page_GetCurrentTextPos(index_page);

        HPDF_Page_ShowText(index_page, text.c_str());

        rect.left = tp.x - 4;
        rect.bottom = tp.y - 4;
        rect.right = HPDF_Page_GetCurrentTextPos(index_page).x + 4;
        rect.top = tp.y + 10;

        HPDF_Page_CreateURILinkAnnot(index_page, rect, link.c_str());

        HPDF_Page_EndText(index_page);
};

void Converter::Render()
{
        std::ifstream in(source_filename_);
        if (!in.is_open())
        {
                std::cerr << "File do not exists" << std::endl;
                throw "File do not exists";
        }
        // Open an input file

        std::string buffer = FileToString(in);

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
        if (!pdf)
        {
                std::cerr << "cannot create PdfDoc object" << std::endl;
                throw "cannot create PdfDoc object";
                return;
        }

        if (setjmp(env))
        {
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
                lines.push_back(buffer.substr(p + (p != 0), (q = buffer.find(sep, p + 1)) - p - (p != 0)));

        // find maximum of size of string in vector
        int max_size = 0;
        for (auto it : lines)
        {
                if (it.size() > max_size)
                {
                        max_size = it.size();
                }
        }

        /* create index page */
        index_page = HPDF_AddPage(pdf);
        HPDF_Page_SetWidth(index_page, (max_size + 5) * 6);
        HPDF_Page_SetHeight(index_page, (lines.size() + 2) * 15);

        // print lines in pdf
        for (int i = 0; i < lines.size() - 1; i++)
                PrintText(index_page, font, lines[i].c_str(), 15, 100 - (i * 10));

        // PrintLink(index_page, font, tp, rect, "sdqqvdsv", "sdvdsv");

        /* save the document to a file */
        HPDF_SaveToFile(pdf, output_filename_.c_str());

        /* clean up */
        HPDF_Free(pdf);
}
