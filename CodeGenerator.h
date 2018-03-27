#ifndef COCO_TO_ANTLR_CODEGENERATOR_H
#define COCO_TO_ANTLR_CODEGENERATOR_H

#include <ostream>
#include <cassert>
#include "common.h"
#include "CocoAstVisitor.h"
#include "Scanner.h"

namespace CocoAST {

    //FIXME: comments can be everywhere
    class CodeGenerator : public CocoAstVisitor {
    public:
        explicit CodeGenerator(std::wostream& output_stream,
                               std::shared_ptr<coco_to_antlr::Buffer> scanner_buffer);

        void visit(Production &ast) override;
        void visit(AttrDecl &ast) override;
        void visit(Expression &ast) override;
        void visit(Term &ast) override;
        void visit(Factor_Braced &ast) override;
        void visit(Factor_Optional &ast) override;
        void visit(Factor_Iterate &ast) override;
        void visit(Factor_ANY &ast) override;
        void visit(Resolver &ast) override;
        void visit(Sym &ast) override;
        void visit(Attribs &ast) override;
        void visit(SemText &ast) override;

    private:
        bool convert_instrumentation = true;
        int indent_level = 0;

        std::wostream& output;
        std::shared_ptr<coco_to_antlr::Buffer> scanner_buffer;

        /** copy the range [pos_start:pos_end) from scanner to output, obeying copy_mode */
        void copy_verbatim(int pos_start, int pos_end, copy_mode mode);

        /**
         * adjust current indent_level by @param increment (positive or negative).
         * @return whitespaces for current/new indentation level
         */
        std::wstring indent(int increment = 0);
    };
}

#endif //COCO_TO_ANTLR_CODEGENERATOR_H
