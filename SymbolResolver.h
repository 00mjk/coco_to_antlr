#ifndef COCO_TO_ANTLR_SYMBOLRESOLVER_H
#define COCO_TO_ANTLR_SYMBOLRESOLVER_H

#include "CocoAstVisitor.h"
#include "CocoAstMain.h"

namespace CocoAST {
    /*!
     * Resolve (production) rule name usage & decorate the AST accordingly. Also compute ANTLR names
     *
     * NOTE: Since TokenDecl is no AST node yet, this sets Sym.antlr_name from token_names filled in .atg
     */
    class SymbolResolver : public CocoAstVisitor {
    public:
        //! ctor. Supply token_names reference to avoid collision of ANTLR production names with ANTLR token names
        explicit SymbolResolver(const c2a_name_map & token_names);

        void visit(Production &ast) override;
        void visit(Factor_Sym &ast) override;

        void accept(std::list<Production> &productions) override;

    private:
        const c2a_name_map& token_names;

        //! coco sym  ->  defining AST
        std::unordered_map<std::wstring, Production&> rule_definitions;
        //! coco sym <-> antlr sym
        c2a_name_map production_names;
        bool resolve_usages;

        std::wstring define_production_name(const std::wstring& coco_name);
    };
}

#endif //COCO_TO_ANTLR_SYMBOLRESOLVER_H
