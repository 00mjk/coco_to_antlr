#ifndef COCO_TO_ANTLR_COCOAST_H
#define COCO_TO_ANTLR_COCOAST_H


#include <string>
#include <memory>
#include <vector>


namespace CocoAST {
    using std::wstring;
    using std::unique_ptr;

    struct CocoAstVisitor;
    struct Production;
    struct Term;
    struct Factor;
    struct Resolver;
    struct Attribs;

    struct CocoAST {
        virtual void visit(CocoAstVisitor &visitor) = 0;

        //TODO: append comments to "currently building" ast
        //TODO: fill pos_start, pos_end in .atg for *all* nodes
        int pos_start, pos_end;
    };

    struct SemText : CocoAST  {
        void visit(CocoAstVisitor &visitor) override;
    };

    struct Sym : CocoAST  {
        void visit(CocoAstVisitor &visitor) override;

        bool literal;
        wstring name;
        wstring antlr_name;
    };

    struct AttrDecl : CocoAST  {
        void visit(CocoAstVisitor &visitor) override;
        //! vector of (type, name, is_output_parameter)
        std::vector< std::tuple<wstring, wstring, bool> > attributes;
    };

    struct Expression : CocoAST  {
        void visit(CocoAstVisitor &visitor) override;
        std::vector<Term> terms;
    };

    struct Term : CocoAST  {
        void visit(CocoAstVisitor &visitor) override;;
        unique_ptr<Resolver> resolver;
        //! the pointers shall never be null (needed only for polymorphism)
        std::vector< unique_ptr<Factor> > factors;
    };

    struct Factor : CocoAST {};

    struct Factor_Sym : Factor  {
        void visit(CocoAstVisitor &visitor) override;
        Sym sym;
        unique_ptr<Attribs> attribs;

        // to be linked by AntlrOptimizer
        Production* referenced_rule;
    };

    struct Factor_Braced : Factor  {
        void visit(CocoAstVisitor &visitor) override;
        Expression expression;
    };

    struct Factor_Optional : Factor  {
        void visit(CocoAstVisitor &visitor) override;
        Expression expression;
    };

    struct Factor_Iterate : Factor  {
        void visit(CocoAstVisitor &visitor) override;
        Expression expression;
    };

    struct Factor_SemText : Factor  {
        void visit(CocoAstVisitor &visitor) override;
        SemText semText;
    };

    struct Factor_ANY : Factor  {
        void visit(CocoAstVisitor &visitor) override;
    };

    struct Factor_SYNC : Factor  {
        void visit(CocoAstVisitor &visitor) override;
    };

    struct Resolver : CocoAST  {
        void visit(CocoAstVisitor &visitor) override;
    };

    struct Attribs : CocoAST  {
        void visit(CocoAstVisitor &visitor) override;

        //! vector of (expr, is_output_parameter)
        std::vector< std::tuple<wstring, bool> > attributes;
    };

    struct Production : CocoAST {
        void visit(CocoAstVisitor &visitor) override;
        wstring name;
        wstring antlr_name;
        unique_ptr<AttrDecl> attr_decl;
        unique_ptr<SemText> sem_text;
        Expression expression;
    };

}

#endif //COCO_TO_ANTLR_COCOAST_H
