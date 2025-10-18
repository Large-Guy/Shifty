#ifndef SHIFTY_FOCUSUPDATE_H
#define SHIFTY_FOCUSUPDATE_H
#include "EventBus/StandardEvents.h"
#include "ECS/System.h"


class FocusUpdate : System<OnUpdate>
{
    void process(const OnUpdate&) override;
};


#endif //SHIFTY_FOCUSUPDATE_H
