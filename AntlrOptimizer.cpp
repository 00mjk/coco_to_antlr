#include "AntlrOptimizer.h"

namespace CocoAST {

    void AntlrOptimizer::visit(Production &ast) {
        if(ast.sem_text) {
            //TODO: inject only if toplevel alternative
            auto new_factor = new Factor_Braced();
            new_factor->expression = std::move(ast.expression);

            ast.expression = Expression();
            ast.expression.terms.emplace_back();
            auto& new_term = ast.expression.terms.back();
            new_term.factors.emplace_back(new_factor);
        }
        CocoAstVisitor::visit(ast);
    }

    void AntlrOptimizer::visit(AttrDecl &ast) {
        CocoAstVisitor::visit(ast);
    }

    void AntlrOptimizer::visit(Attribs &ast) {
        CocoAstVisitor::visit(ast);
    }

    void AntlrOptimizer::visit(Factor_Sym &ast) {
        CocoAstVisitor::visit(ast);
    }

}
