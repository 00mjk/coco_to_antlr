#include "CocoAstMain.h"

#include "AntlrOptimizer.h"
#include "CodeGenerator.h"
#include "SymbolResolver.h"


namespace CocoAST {

    void generate_antlr_code(std::wostream& output,
                             coco_to_antlr::Buffer* scanner_buffer,
                             const c2a_name_map & token_names,
                             std::list<Production>& productions_ast)
    {
        SymbolResolver(token_names).accept(productions_ast);
        AntlrOptimizer().accept(productions_ast);
        CodeGenerator(output, scanner_buffer).accept(productions_ast);
    }
}
