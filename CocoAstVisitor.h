#ifndef COCO_TO_ANTLR_COCOASTVISITOR_H
#define COCO_TO_ANTLR_COCOASTVISITOR_H

#include <list>
#include "CocoAST.h"

namespace CocoAST {

    struct CocoAstVisitor {
        //virtual void visit(CocoAST& ast);
        virtual void accept(std::list<Production> &productions);

        virtual void visit(Production& ast);
        virtual void visit(AttrDecl& ast);
        virtual void visit(Expression& ast);
        virtual void visit(Term& ast);
        virtual void visit(Factor_Sym& ast);
        virtual void visit(Factor_Braced& ast);
        virtual void visit(Factor_Optional& ast);
        virtual void visit(Factor_Iterate& ast);
        virtual void visit(Factor_SemText& ast);
        virtual void visit(Factor_ANY& ast);
        virtual void visit(Factor_SYNC& ast);
        virtual void visit(Resolver& ast);
        virtual void visit(Sym& ast);
        virtual void visit(Attribs& ast);
        virtual void visit(SemText& ast);

    };

};


#endif //COCO_TO_ANTLR_COCOASTVISITOR_H
