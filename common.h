#pragma once

#include <unordered_map>
#include <algorithm>
#include <regex>


#define C2A_TODO "FIXME (coco_to_antlr): "

template<class Key, class Value>
class UBiMap {
private:
    std::unordered_map<Key, Value> forward;
    std::unordered_map<Value, Key> backward;

public:
    void insert(Key key, Value value) {
        forward.insert({key, value});
        backward.insert({value, key});
    }

    bool contains_key(const Key& key) {
        return forward.find(key) != forward.end();
    }

    bool contains_value(const Value& value) {
        return backward.find(value) != backward.end();
    }

    Value& at(const Key& key) {
        return forward.at(key);
    }
};


enum class name_type { charset, token, production };


const std::wstring coco_and_antlr_escaped_chars = L"nrbtf'\\";

//TODO: parser fields without match in ANTLR (probably not needed): lookahead `la`, `scanner`, `SynErr`
//TODO: -> is Coco C++ target only
/** Matches references to the current (i.e. last matched) token in coco. */
const std::wregex token_object_regex(L"t\\s*->\\s*((kind)|(val)|(pos)|(charPos)|(line)|(col))");
/** Specifies how to map above references to ANTLR.
 * See https://github.com/antlr/antlr4/blob/master/doc/actions.md#token-attributes and the Coco User Manual
 */
//FIXME: $stop "attribute is available only to the after and finally actions". instead, remember last token/rule name and insert $name instead of "$stop"
const std::unordered_map<size_t, std::wstring> token_object_replace_map = {
        {2, L"$ctx.stop.type"},  // token type/kind
        {3, L"$ctx.stop.text"},  // token value
        {4, L"$ctx.stop.index"}, // token position (Coco: in bytes)
        {5, L"$ctx.stop.index"}, // token position (Coco: in characters)
        {6, L"$ctx.stop.line"},  // line
        {7, L"$ctx.stop.pos"},   // column
};
