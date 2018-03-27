#include "CocoAstVisitor.h"
#include <cassert>


namespace CocoAST {

    //void CocoAstVisitor::visit(CocoAST &ast) {}

    void CocoAstVisitor::visit(Production &ast) {
        if(ast.attr_decl)
            ast.attr_decl->visit(*this);
        if(ast.sem_text)
            ast.sem_text->visit(*this);
        ast.expression.visit(*this);
    }

    void CocoAstVisitor::visit(AttrDecl &ast) {}

    void CocoAstVisitor::visit(Expression &ast) {
        for(auto& term : ast.terms)
            term.visit(*this);
    }

    void CocoAstVisitor::visit(Term &ast) {
        if(ast.resolver)
            ast.resolver->visit(*this);
        for(auto& factor : ast.factors) {
            assert(factor);
            factor->visit(*this);
        }
    }

    void CocoAstVisitor::visit(Factor_Sym &ast) {
        ast.sym.visit(*this);
        if(ast.attributes)
            ast.attributes->visit(*this);
    }

    void CocoAstVisitor::visit(Factor_Braced &ast) {
        ast.expression.visit(*this);
    }

    void CocoAstVisitor::visit(Factor_Optional &ast) {
        ast.expression.visit(*this);
    }

    void CocoAstVisitor::visit(Factor_Iterate &ast) {
        ast.expression.visit(*this);
    }

    void CocoAstVisitor::visit(Factor_SemText &ast) {
        ast.semText.visit(*this);
    }

    void CocoAstVisitor::visit(Factor_ANY &ast) {}

    void CocoAstVisitor::visit(Resolver &ast) {}

    void CocoAstVisitor::visit(Sym &ast) {}

    void CocoAstVisitor::visit(Attribs &ast) {}

    void CocoAstVisitor::visit(SemText &ast) {}

}
