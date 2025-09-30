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

    static void addChild(Entity to, Entity add)
    {
        if (!to.has<Layout>())
            throw std::runtime_error("Parent entity is missing layout component");
        if (!add.has<Layout>())
            throw std::runtime_error("Child entity is missing layout component!");
        ComRef<Layout> layout = to.get<Layout>();
        ComRef<Layout> other = add.get<Layout>();
        if (other->parent != nullptr)
        {
            removeChild(other->parent, add);
        }
        other->parent = to;
        layout->children.push_back(add);
    }

    static void removeChild(Entity from, Entity remove)
    {
        if (!from.has<Layout>())
            throw std::runtime_error("Parent entity is missing layout component");
        if (!remove.has<Layout>())
            throw std::runtime_error("Child entity is missing layout component!");
        ComRef<Layout> layout = from.get<Layout>();
        auto iter = std::find(layout->children.begin(), layout->children.end(), remove);
        layout->children.erase(iter);
        remove.get<Layout>()->parent = {0};
    }
};

#endif //SHIFTY_LAYOUT_H
