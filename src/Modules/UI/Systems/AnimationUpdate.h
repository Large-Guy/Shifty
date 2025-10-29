#ifndef SHIFTY_ANIMATIONUPDATE_H
#define SHIFTY_ANIMATIONUPDATE_H
#include "EventBus/StandardEvents.h"
#include "ECS/System.h"


class AnimationUpdate final : System<OnUpdate>
{
    void process(OnUpdate&) override;
};


#endif //SHIFTY_ANIMATIONUPDATE_H
