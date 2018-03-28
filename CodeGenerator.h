#ifndef COCO_TO_ANTLR_CODEGENERATOR_H
#define COCO_TO_ANTLR_CODEGENERATOR_H

#include <ostream>
#include <cassert>
#include <set>
#include "common.h"
#include "CocoAstVisitor.h"
#include "Scanner.h"

namespace CocoAST {

    //FIXME: comments can be everywhere, check getHiddenTokensToLeft() <https://stackoverflow.com/a/37252830>
    class CodeGenerator : public CocoAstVisitor {
    public:
        explicit CodeGenerator(std::wostream& output_stream,
                               coco_to_antlr::Buffer* scanner_buffer);

        void visit(Production &ast) override;
        void visit(AttrDecl &ast) override;
        void visit(Expression &ast) override;
        void visit(Term &ast) override;
        //NOTE: we convert `Attribs` with Factor_Sym because we need the context
        void visit(Factor_Sym& ast) override;
        void visit(Factor_Braced &ast) override;
        void visit(Factor_Optional &ast) override;
        void visit(Factor_Iterate &ast) override;
        void visit(Factor_ANY &ast) override;
        void visit(Resolver &ast) override;
        void visit(Sym &ast) override;
        void visit(SemText &ast) override;

    private:
        bool convert_instrumentation = true;
        int indent_level = 0;

        std::wostream& output;
        coco_to_antlr::Buffer* scanner_buffer;

        /** copy the range [pos_start:pos_end) from scanner to os, obeying copy_mode */
        void copy_verbatim(std::wostream& output, int pos_start, int pos_end, copy_mode mode);

        /**
         * adjust current indent_level by @param increment (positive or negative).
         * @return whitespaces for current/new indentation level
         */
        std::wstring indent(int increment = 0);

        /*! in expr, prefix names from current_scope_attrdecl with $
         * TODO: a less hackish approach, probably in a (separate?) visitor
         */
        std::wstring replace_current_scope_attr(const std::wstring& expr);
        std::wregex current_scope_attr_regex;
        void build_scope_attr_regex(const AttrDecl& attr_decl);
    };
}

#endif //COCO_TO_ANTLR_CODEGENERATOR_H
