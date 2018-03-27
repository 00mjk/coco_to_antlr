#ifndef COCO_TO_ANTLR_ANTLROPTIMIZER_H
#define COCO_TO_ANTLR_ANTLROPTIMIZER_H

#include "CocoAstVisitor.h"

namespace CocoAST {
    class AntlrOptimizer : public CocoAstVisitor{
    public:
        void visit(Production &ast) override;
        void visit(AttrDecl &ast) override;
        void visit(Factor_Sym &ast) override;
    };
}


#endif //COCO_TO_ANTLR_ANTLROPTIMIZER_H
