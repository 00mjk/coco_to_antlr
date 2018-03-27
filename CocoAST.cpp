#include "CocoAST.h"
#include "CocoAstVisitor.h"

namespace CocoAST {
    //void CocoAST::CocoAST::visit(CocoAstVisitor &visitor) { visitor.visit(*this); }

    void Production::visit(CocoAstVisitor &visitor) { visitor.visit(*this); }

    void AttrDecl::visit(CocoAstVisitor &visitor) { visitor.visit(*this); }

    void Expression::visit(CocoAstVisitor &visitor) { visitor.visit(*this); }

    void Term::visit(CocoAstVisitor &visitor) { visitor.visit(*this); }

    void Factor_Sym::visit(CocoAstVisitor &visitor) { visitor.visit(*this); }

    void Factor_Braced::visit(CocoAstVisitor &visitor) { visitor.visit(*this); }

    void Factor_Optional::visit(CocoAstVisitor &visitor) { visitor.visit(*this); }

    void Factor_Iterate::visit(CocoAstVisitor &visitor) { visitor.visit(*this); }

    void Factor_SemText::visit(CocoAstVisitor &visitor) { visitor.visit(*this); }

    void Factor_ANY::visit(CocoAstVisitor &visitor) { visitor.visit(*this); }

    void Resolver::visit(CocoAstVisitor &visitor) { visitor.visit(*this); }

    void Sym::visit(CocoAstVisitor &visitor) { visitor.visit(*this); }

    void Attribs::visit(CocoAstVisitor &visitor) { visitor.visit(*this); }

    void SemText::visit(CocoAstVisitor &visitor) { visitor.visit(*this); }

}
