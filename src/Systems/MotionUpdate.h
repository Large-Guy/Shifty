#ifndef SHIFTY_MOTIONUPDATE_H
#define SHIFTY_MOTIONUPDATE_H
#include "Events.h"
#include "ECS/System.h"


class MotionUpdate : System<OnUpdate>
{
    void process(const OnUpdate&) override;
};


#endif //SHIFTY_MOTIONUPDATE_H
