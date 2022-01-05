
#ifndef CONVERTER_H_
#define CONVERTER_H_

#include <fstream>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include <iostream>
#include <fstream>
#include <vector>
extern "C"
{
#include "hpdf.h"
}
extern jmp_buf env;

class Converter
{
public:
        Converter(const std::string &source_filename) : source_filename_(source_filename){};

        void Render();

        ~Converter(){};

private:
        std::string source_filename_;
        const std::string output_filename_ = "converted.pdf";
};

#endif