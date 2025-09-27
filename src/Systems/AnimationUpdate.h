#ifndef SHIFTY_ANIMATIONUPDATE_H
#define SHIFTY_ANIMATIONUPDATE_H
#include "Events.h"
#include "ECS/System.h"


class AnimationUpdate final : System<OnUpdate>
{
    void process(const OnUpdate&) override;
};


#endif //SHIFTY_ANIMATIONUPDATE_H
