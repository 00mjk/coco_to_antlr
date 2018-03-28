#include <cassert>
#include "SymbolResolver.h"

namespace CocoAST {

    SymbolResolver::SymbolResolver(const c2a_name_map & token_names) :
            token_names(token_names)
    {}

    void SymbolResolver::visit(Production &ast) {
        rule_definitions.insert({ast.name, ast});
        if(resolve_usages) {
            ast.antlr_name = define_production_name(ast.name);
        }
        CocoAstVisitor::visit(ast);
    }

    void SymbolResolver::visit(Factor_Sym &ast) {
        if (ast.sym.literal || !resolve_usages)
            return;
        const auto& coco_name = ast.sym.name;

        if(token_names.contains_key(coco_name)) {
            ast.sym.antlr_name = std::wstring(token_names.at(coco_name));
            return;
        }
        // else: must be a production rule reference
        assert(! ast.referenced_rule);
        // decorate with rule definition ...
        if (rule_definitions.find(coco_name) != rule_definitions.end()) {
            ast.referenced_rule = &rule_definitions.at(coco_name);
            if(ast.referenced_rule->attr_decl) {
                assert(ast.attribs);
                // ... copy attribute detail ...
                auto& use = ast.attribs->attributes;
                auto& def = ast.referenced_rule->attr_decl->attributes;
                assert(def.size() == use.size());
                for(auto i = 0; i < def.size(); ++i) {
                    // set use[i].is_output_parameter = def[i].is_output_parameter
                    std::get<bool>(use[i])  =  std::get<bool>(def[i]);
                }
            }
        } else {
            //TODO: report not resolvable rule (if not token)
        }

        // ... and define ANTLR name
        ast.sym.antlr_name = define_production_name(coco_name);

        //not needed: sym, attribs not implemented here, anyway: CocoAstVisitor::visit(ast);
    }

    void SymbolResolver::accept(std::list<Production> &productions) {
        resolve_usages = false;
        // first pass: find names
        CocoAstVisitor::accept(productions);
        resolve_usages = true;
        // second pass: decorate name usage ASTs
        CocoAstVisitor::accept(productions);
    }

    std::wstring SymbolResolver::define_production_name(const std::wstring &coco_name) {
        if(production_names.contains_key(coco_name)) {
            return production_names.at(coco_name);
        } else {
            auto antlr_name_raw = coco_name.substr(coco_name.find_first_not_of(L'_'));
            antlr_name_raw[0] = std::tolower((unsigned char) antlr_name_raw[0]);
            auto antlr_name = antlr_name_raw;
            size_t i = 2;
            while (production_names.contains_value(antlr_name)
                   || token_names.contains_value(antlr_name)) {
                antlr_name = antlr_name_raw + L"_" + std::to_wstring(i);
                ++i;
            }
            production_names.insert(coco_name, antlr_name);
            return antlr_name;
        }
    }
}
