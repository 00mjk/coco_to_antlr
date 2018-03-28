#ifndef COCO_TO_ANTLR_COCOASTMAIN_H
#define COCO_TO_ANTLR_COCOASTMAIN_H

#include <ostream>
#include <list>
#include "CocoAST.h"
#include "Scanner.h"
#include "common.h"


namespace CocoAST {
    using c2a_name_map = UBiMap<std::wstring, std::wstring>;

    void generate_antlr_code(std::wostream& output,
                             coco_to_antlr::Buffer* scanner_buffer,
                             const c2a_name_map & token_names,
                             std::list<Production>& productions_ast);

}


#endif //COCO_TO_ANTLR_COCOASTMAIN_H
