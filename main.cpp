#include <vector>
#include <fstream>
#include <iostream>
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


int main(int argc, char* argv[]) {
    using namespace coco_to_antlr;
    const std::vector<std::string> arguments(argv, argv + argc);
    if (arguments.size() < 2) {
        std::wcerr << L"not enough arguments!\n";
        usage();
        return 1;
    }

    coco_wstring_t input_name(arguments.at(1).c_str());
    auto scanner = std::make_unique<Scanner>(input_name.raw());
    auto parser = std::make_unique<Parser>(scanner.get());
    std::wofstream output_file;
    if (arguments.size() >= 3) {
        output_file.open(arguments.at(2));
        parser->output_stream = output_file;
    }
    parser->Parse();
    return 0;
}
