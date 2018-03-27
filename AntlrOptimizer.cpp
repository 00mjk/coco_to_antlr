#include "AntlrOptimizer.h"

namespace CocoAST {

    void AntlrOptimizer::visit(Production &ast) {
        CocoAstVisitor::visit(ast);
    }

    void AntlrOptimizer::visit(AttrDecl &ast) {
        CocoAstVisitor::visit(ast);
    }

    void AntlrOptimizer::visit(Factor_Sym &ast) {
        CocoAstVisitor::visit(ast);
    }

}
