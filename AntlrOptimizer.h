#ifndef COCO_TO_ANTLR_ANTLROPTIMIZER_H
#define COCO_TO_ANTLR_ANTLROPTIMIZER_H

#include "CocoAstVisitor.h"

namespace CocoAST {

    /*!
     * Ensure the AST is suitable for ANTLR output.
     *
     * 1. if Production has a SemText, ensure its Expression is wrapped in Braces,
     *    otherwise the SemText would end up only in the first alternative
     * 2. FIXME: Rewrite Sym names
     * 3. FIXME: Rewrite output (i.e. C++ reference) attributes (rule parameters/arguments) to @ returns[] spec
     * 4. TODO: if Factor_Braced|Optional|Iterate contains only one thing (sym|ANY|SemText, without Resolver), remove braces?
     */
    class AntlrOptimizer : public CocoAstVisitor{
    public:
        void visit(Production &ast) override;
        void visit(AttrDecl &ast) override;
        void visit(Attribs &ast) override;
        void visit(Factor_Sym &ast) override;
    };
}


#endif //COCO_TO_ANTLR_ANTLROPTIMIZER_H
