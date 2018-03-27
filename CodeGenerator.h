#ifndef COCO_TO_ANTLR_CODEGENERATOR_H
#define COCO_TO_ANTLR_CODEGENERATOR_H

#include "CocoAstVisitor.h"

namespace CocoAST {
    class CodeGenerator : public CocoAstVisitor {
    public:
        void visit(Production &ast) override;
        void visit(AttrDecl &ast) override;
        void visit(Expression &ast) override;
        void visit(Term &ast) override;
        void visit(Factor_Sym &ast) override;
        void visit(Factor_Braced &ast) override;
        void visit(Factor_Optional &ast) override;
        void visit(Factor_Iterate &ast) override;
        void visit(Factor_SemText &ast) override;
        void visit(Factor_ANY &ast) override;
        void visit(Resolver &ast) override;
        void visit(Sym &ast) override;
        void visit(Attribs &ast) override;
        void visit(SemText &ast) override;

    private:
        int indent_level = 0;
    };
}

#endif //COCO_TO_ANTLR_CODEGENERATOR_H
