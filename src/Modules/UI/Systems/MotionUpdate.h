#ifndef SHIFTY_MOTIONUPDATE_H
#define SHIFTY_MOTIONUPDATE_H
#include "EventBus/StandardEvents.h"
#include "ECS/System.h"


class MotionUpdate : System<OnUpdate>
{
    void process(OnUpdate&) override;
};


#endif //SHIFTY_MOTIONUPDATE_H