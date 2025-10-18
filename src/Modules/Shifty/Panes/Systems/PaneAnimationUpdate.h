#ifndef SHIFTY_VIEWANIMATIONUPDATE_H
#define SHIFTY_VIEWANIMATIONUPDATE_H
#include "EventBus/StandardEvents.h"
#include "ECS/System.h"


class PaneAnimationUpdate : System<OnUpdate>
{
    void process(const OnUpdate&) override;
};


#endif //SHIFTY_VIEWANIMATIONUPDATE_H
