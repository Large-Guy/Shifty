#ifndef SHIFTY_DRAWRENDER_H
#define SHIFTY_DRAWRENDER_H
#include "ECS/System.h"
#include "EventBus/StandardEvents.h"

class DrawRender final : System<OnRender>
{
    void process(OnRender&) override;
};


#endif //SHIFTY_DRAWRENDER_H
