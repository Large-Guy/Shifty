#ifndef SHIFTY_TABVIEW_H
#define SHIFTY_TABVIEW_H
#include "ECS/Entity.h"

class TabviewShared
{
public:
    static void show();
    static void hide();
    static void swap(Entity tab);
};

#endif //SHIFTY_TABVIEW_H
