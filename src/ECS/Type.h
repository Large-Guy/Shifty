#ifndef SHIFTY_TYPE_H
#define SHIFTY_TYPE_H
#include <vector>

#include "Component.h"


using Type = std::vector<Component>;

struct TypeHash {
    std::size_t operator()(const Type &type) const {
        std::size_t seed = 0;

        for (auto &item: type) {
            ComponentHash componentHash = {};
            seed ^= std::hash<unsigned int>{}(componentHash(item)) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

#endif //SHIFTY_TYPE_H
