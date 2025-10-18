#ifndef SHIFTY_APPUPDATE_H
#define SHIFTY_APPUPDATE_H
#include "EventBus/StandardEvents.h"
#include "ECS/System.h"

class AppUpdate final : System<OnUpdate>
{
    void process(const OnUpdate& _update) override;
};

#endif //SHIFTY_APPUPDATE_H
