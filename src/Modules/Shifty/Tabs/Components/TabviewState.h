#ifndef SHIFTY_TABVIEWSTATE_H
#define SHIFTY_TABVIEWSTATE_H
#include "ECS/Entity.h"

struct TabviewState
{
    bool active = false;
    Entity targetView = Entity::null;
    int page = 0;
    Entity focusedTab = Entity::null;
};

#endif //SHIFTY_TABVIEWSTATE_H
