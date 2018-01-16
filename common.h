#pragma once

#include <unordered_map>
#include <algorithm>


#define C2A_TODO "TODO (coco_to_antlr): "

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
