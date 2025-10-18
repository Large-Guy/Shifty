#ifndef SHIFTY_HIERARCHY_H
#define SHIFTY_HIERARCHY_H

#include "ECS/Entity.h"
#include <vector>

struct Hierarchy
{
    Entity parent = Entity::null;
    std::vector<Entity> children = {};
};

#endif //SHIFTY_HIERARCHY_H
