#ifndef SHIFTY_TABSYSTEMGROUP_H
#define SHIFTY_TABSYSTEMGROUP_H
#include "Systems/TabViewUpdate.h"
#include "Systems/Input/TabViewClick.h"
#include "Systems/Input/TabViewKeydown.h"

struct TabViewSystemGroup
{
    TabViewKeydown tabKeydown{};
    TabViewUpdate tabViewUpdate{};
    TabViewClick tabViewClick{};
};

#endif //SHIFTY_TABSYSTEMGROUP_H
