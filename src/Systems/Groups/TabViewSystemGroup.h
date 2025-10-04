#ifndef SHIFTY_TABSYSTEMGROUP_H
#define SHIFTY_TABSYSTEMGROUP_H
#include "Systems/TabviewUpdate.h"
#include "Systems/Input/TabviewClick.h"
#include "Systems/Input/TabviewKeydown.h"

struct TabViewSystemGroup
{
    TabviewKeydown tabKeydown{};
    TabviewUpdate tabViewUpdate{};
    TabviewClick tabViewClick{};
};

#endif //SHIFTY_TABSYSTEMGROUP_H
