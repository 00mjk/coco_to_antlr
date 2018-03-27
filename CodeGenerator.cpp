#include "CodeGenerator.h"

namespace CocoAST {
    void CodeGenerator::visit(Production &ast) {
        CocoAstVisitor::visit(ast);
    }

    void CodeGenerator::visit(AttrDecl &ast) {
        CocoAstVisitor::visit(ast);
    }

    void CodeGenerator::visit(Expression &ast) {
        CocoAstVisitor::visit(ast);
    }

    void CodeGenerator::visit(Term &ast) {
        CocoAstVisitor::visit(ast);
    }

    void CodeGenerator::visit(Factor_Sym &ast) {
        CocoAstVisitor::visit(ast);
    }

    void CodeGenerator::visit(Factor_Braced &ast) {
        CocoAstVisitor::visit(ast);
    }

    void CodeGenerator::visit(Factor_Optional &ast) {
        CocoAstVisitor::visit(ast);
    }

    void CodeGenerator::visit(Factor_Iterate &ast) {
        CocoAstVisitor::visit(ast);
    }

    void CodeGenerator::visit(Factor_SemText &ast) {
        CocoAstVisitor::visit(ast);
    }

    void CodeGenerator::visit(Factor_ANY &ast) {
        CocoAstVisitor::visit(ast);
    }

    void CodeGenerator::visit(Resolver &ast) {
        CocoAstVisitor::visit(ast);
    }

    void CodeGenerator::visit(Sym &ast) {
        CocoAstVisitor::visit(ast);
    }

    void CodeGenerator::visit(Attribs &ast) {
        CocoAstVisitor::visit(ast);
    }

    void CodeGenerator::visit(SemText &ast) {
        CocoAstVisitor::visit(ast);
    }
}
