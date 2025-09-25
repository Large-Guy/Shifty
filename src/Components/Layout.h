#ifndef SHIFTY_LAYOUT_H
#define SHIFTY_LAYOUT_H

#include <memory>
#include <unordered_map>
#include <vector>

#include "../ECS/Entity.h"

/**
 * @class Layout
 * @brief Handles layouts of open views/panels.
 */
struct Layout {
    enum class Type {
        FULL,
        VERTICAL,
        HORIZONTAL
    };

    enum class Mode {
        DISABLE,
        PERCENT,
    };

    Type type = Type::FULL;

    Mode widthMode = Mode::DISABLE;
    float width = 0;
    Mode heightMode = Mode::DISABLE;
    float height = 0;
};

#endif //SHIFTY_LAYOUT_H
