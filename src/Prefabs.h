#ifndef SHIFTY_PREFABS_H
#define SHIFTY_PREFABS_H
#include "Components/Layout.h"
#include "ECS/Entity.h"


class Prefabs
{
public:
    static Entity createView();
    static Entity createLayout(Layout::Type type);
};


#endif //SHIFTY_PREFABS_H
