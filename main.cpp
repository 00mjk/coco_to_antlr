#include <vector>
#include <fstream>
#include <iostream>
#include <codecvt>
#include "Parser.h"


//! wrapper around coco_string_* functions
class coco_wstring_t {
public:
    explicit coco_wstring_t(const char* value) :
            data(coco_string_create(value))
    {};
    ~coco_wstring_t() {
        coco_string_delete(data);
    }
    wchar_t* raw() { return data; }
private:
    wchar_t* data;
};


void usage() {
    std::wcout << L"compiled " __DATE__ << " " << __TIME__
               << L"\nUsage: coco_to_antlr Coco.atg [ antlr.g4 ]\n\n"
               << L"\tConvert the Coco/R grammar Coco.atg to an ANTLR4 grammar, written to antlr.g4 or standard output.\n";
}


void do_parse(coco_wstring_t input, std::reference_wrapper<std::wostream> output) {
    using namespace coco_to_antlr;
    auto scanner = std::make_unique<Scanner>(input.raw());
    auto parser = std::make_unique<Parser>(scanner.get());
    parser->output_stream = output;
    parser->Parse();
}


int main(int argc, char* argv[]) {
    const std::vector<std::string> arguments(argv, argv + argc);
    if (arguments.size() < 2) {
        std::wcerr << L"not enough arguments!\n";
        usage();
        return 1;
    }

    coco_wstring_t input_name(arguments.at(1).c_str());
    if (arguments.size() >= 3) {
        std::locale locale(std::locale::classic(), new std::codecvt_utf8<wchar_t>); // necessary to output non-ASCII, see <https://stackoverflow.com/a/3950795>
        std::wofstream output_file(arguments.at(2));
        output_file.imbue(locale);
        do_parse(input_name, output_file);
    } else {
        do_parse(input_name, std::ref(std::wcout));
    }
    return 0;
}
