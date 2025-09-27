#ifndef SHIFTY_LAYOUT_H
#define SHIFTY_LAYOUT_H
#include <vector>

#include "ECS/Entity.h"

/**
 * @class Layout
 * @brief Handles layouts of open views/panels.
 */
struct Layout
{
    enum class Type
    {
        FREE,
        FULL,
        VERTICAL,
        HORIZONTAL
    };

    Type type = Type::FULL;

    Entity parent = Entity();
    std::vector<Entity> children = {};

    static void addChild(Entity to, Entity add);

    static void removeChild(Entity from, Entity remove);
};

#endif //SHIFTY_LAYOUT_H
