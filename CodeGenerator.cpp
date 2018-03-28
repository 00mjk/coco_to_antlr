#include "CodeGenerator.h"

#include <utility>

namespace CocoAST {

    CodeGenerator::CodeGenerator(std::wostream& output_stream,
                                 coco_to_antlr::Buffer* scanner_buffer) :
            CocoAstVisitor(),
            output(output_stream),
            scanner_buffer(scanner_buffer)
    {
        assert(scanner_buffer);
    }


    void CodeGenerator::visit(Production &ast) {
        output << ast.antlr_name;
        if(ast.attr_decl) {
            ast.attr_decl->visit(*this);
        }
        output << ":\n";
        indent(+1);
        if(ast.sem_text) {
            output << indent();
            ast.sem_text->visit(*this);
            output << "\n";
        }
        ast.expression.visit(*this);
        output << "\n" << indent(-1) << ";\n";
        output << "\n";
    }

    void CodeGenerator::visit(AttrDecl &ast) {
        if(! convert_instrumentation)
            return;
        if(ast.attributes.empty())
            return;

        for(bool check_output : {false, true}) {
            bool first = true;
            for (auto &attr : ast.attributes) {
                auto& type = std::get<0>(attr);
                auto& name = std::get<1>(attr);
                auto& is_output_parameter = std::get<bool>(attr);
                if (check_output == is_output_parameter) {
                    if (first) {
                        first = false;
                        if(check_output)
                            output << " returns";
                        output << "[";
                    } else {
                        output << ", ";
                    }
                    output << type << " " << name;
                }
            }
            if(!first)
                output << "]";
        }
    }

    void CodeGenerator::visit(Expression &ast) {
        output << indent();
        bool first = true;
        for(auto& term : ast.terms) {
            if(first) {
                first = false;
            } else {
                output << "\n" << indent(-1) << "|\t";
                indent(+1);
            }
            term.visit(*this);
        }
    }

    void CodeGenerator::visit(Term &ast) {
        if(ast.resolver)
            ast.resolver->visit(*this);
        bool first = true;
        for(auto& factor : ast.factors) {
            assert(factor);
            if(first) {
                first = false;
            } else {
                output << "\n" << indent();
            }
            factor->visit(*this);
        }
    }

    void CodeGenerator::visit(Factor_Sym& ast) {
        ast.sym.visit(*this);

        if(! ast.attribs)
            return;
        if(! convert_instrumentation)
            return;
        auto& attribs = *ast.attribs;
        if(attribs.attributes.empty())
            return;
        assert(ast.referenced_rule);

        //TODO: prefix arguments of surrounding AttrDecl with $

        // first, add non-output parameters in []
        bool first = true;
        size_t i = 0;
        for (auto &attr : attribs.attributes) {
            auto& expr = std::get<0>(attr);
            auto& is_output_parameter = std::get<bool>(attr);
            if (! is_output_parameter) {
                if (first) {
                    first = false;
                    output << "[";
                } else {
                    output << ", ";
                }
                output << expr;
            }
            ++i;
        }
        if(!first)
            output << "]";

        // second, assign output parameters, which are fields of the returned context in ANTLR
        first = true;
        bool second = false; // false iff we output exactly one parameter: then } will be on the same line
        i = 0;
        for (auto &attr : attribs.attributes) {
            auto& expr = std::get<0>(attr);
            auto& is_output_parameter = std::get<1>(attr);
            if (is_output_parameter) {
                if(first) {
                    first = false;
                    output << "\n" << indent() << "{ ";
                    indent(+1);
                } else {
                    second = true;
                    output << "\n" << indent();
                }
                auto attr_decl = ast.referenced_rule->attr_decl->attributes.at(i);
                auto decl_name = std::get<1>(attr_decl);
                output << expr << " = $" << ast.sym.antlr_name << "." << decl_name << ";";
            }
            ++i;
        }
        if(!first) {
            indent(-1);
            if(second)
                output << "\n" << indent();
            else
                output << " ";
            output << "}";
        }

    }

    void CodeGenerator::visit(Factor_Braced &ast) {
        output << "(\n";
        indent(+1);
        ast.expression.visit(*this);
        output << '\n' << indent(-1) << ')';
    }

    void CodeGenerator::visit(Factor_Optional &ast) {
        output << "(\n"; indent(+1);
        ast.expression.visit(*this);
        output << '\n' << indent(-1) << ")?";
    }

    void CodeGenerator::visit(Factor_Iterate &ast) {
        output << "(\n"; indent(+1);
        ast.expression.visit(*this);
        output << '\n' << indent(-1) << ")*";
    }

    void CodeGenerator::visit(Factor_ANY &ast) {
        output << '.';
        output << " /*" C2A_TODO "implement Coco ANY in ANTLR lexer, not possible in parser */\n";
    }

    void CodeGenerator::visit(Resolver &ast) {
        if(! convert_instrumentation)
            return;

        output << "/* " C2A_TODO "IF() conflict resolver from Coco, check ANTLR code:\n";
        copy_verbatim(ast.pos_start, ast.pos_end, copy_mode::replace);
        output << "\n*/\n" << indent();
    }

    void CodeGenerator::visit(Sym &ast) {
        if (ast.literal) {
            output << "'" << ast.name << "'";
        } else {
            output << ast.antlr_name;
        }
    }

    void CodeGenerator::visit(SemText &ast) {
        if(! convert_instrumentation)
            return;

        output << "{ ";
        copy_verbatim(ast.pos_start, ast.pos_end, copy_mode::replace);
        output << " }";
    }

    std::wstring CodeGenerator::indent(int increment) {
        indent_level += increment;
        assert(indent_level >= 0);
        indent_level = std::max(0, indent_level);
        return std::wstring(indent_level, '\t');
    }

    void CodeGenerator::copy_verbatim(int pos_start, int pos_end, copy_mode mode) {
        const wchar_t* attr = scanner_buffer->GetString(pos_start, pos_end);
        switch(mode) {
            case copy_mode::copy:
                output << attr;
                break;

            case copy_mode::warn:
                if (std::regex_search(attr, token_object_regex))
                    output << L"/*" C2A_TODO "references to current Coco Token in this code block, adjust for ANTLR: */\n";
                output << attr;
                break;

            case copy_mode::replace: {
                std::wcmatch match;
                // cannot use regex_iterator because it doesn't give us access to rest behind last match (here: attr after loop)
                // cannot use regex_token_iterator because it doesn't tell us index of matched subgroup
                while (std::regex_search(attr, match, token_object_regex)) {
                    output << match.prefix();
                    for (size_t i = 2; i < match.size(); ++i) { // all relevant groups
                        auto sub_match = match[i];
                        if (sub_match.matched) {
                            output << token_object_replace_map.at(i);
                            attr = sub_match.second; // rest of the input
                            break;
                        }
                    }
                }
                output << attr;
                break;
            }
        }
    }
}
