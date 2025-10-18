#ifndef SHIFTY_HIERARCHYSYSTEM_H
#define SHIFTY_HIERARCHYSYSTEM_H

#include <algorithm>

#include "Hierarchy/Components/Hierarchy.h"
#include "ECS/Entity.h"

namespace HierarchySystem
{
    static void removeTab(Entity viewEntity, Entity tabEntity)
    {
        ComRef<Hierarchy> view = viewEntity.get<Hierarchy>();
        ComRef<Hierarchy> tab = tabEntity.get<Hierarchy>();

        auto iter = std::find(view->children.begin(), view->children.end(), tabEntity);
        view->children.erase(iter);
        tab->parent = Entity::null;
    }

    static void addTab(Entity viewEntity, Entity tabEntity)
    {
        ComRef<Hierarchy> view = viewEntity.get<Hierarchy>();
        ComRef<Hierarchy> tab = tabEntity.get<Hierarchy>();

        if (tab->parent != Entity::null)
        {
            removeTab(tab->parent, tabEntity);
        }

        view->children.insert(view->children.begin(), tabEntity);
        tab->parent = viewEntity;
    }
}

#endif //SHIFTY_HIERARCHYSYSTEM_H
