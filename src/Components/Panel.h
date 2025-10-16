#ifndef SHIFTY_VIEW_H
#define SHIFTY_VIEW_H

#include <SDL3/SDL_render.h>

#include "Tab.h"
#include <algorithm>

struct Panel
{
    std::vector<Entity> holdingTabs;

    static void removeTab(Entity viewEntity, Entity tabEntity)
    {
        ComRef<Panel> view = viewEntity.get<Panel>();
        ComRef<Tab> tab = tabEntity.get<Tab>();

        auto iter = std::find(view->holdingTabs.begin(), view->holdingTabs.end(), tabEntity);
        view->holdingTabs.erase(iter);
        tab->viewer = {0};
    }

    static void addTab(Entity viewEntity, Entity tabEntity)
    {
        ComRef<Panel> view = viewEntity.get<Panel>();
        ComRef<Tab> tab = tabEntity.get<Tab>();

        if (tab->viewer != Entity::null)
        {
            removeTab(tab->viewer, tabEntity);
        }

        view->holdingTabs.insert(view->holdingTabs.begin(), tabEntity);
        tab->viewer = viewEntity;
    }
};


#endif //SHIFTY_VIEW_H
