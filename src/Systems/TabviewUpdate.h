#ifndef SHIFTY_NAVIGATIONUPDATE_H
#define SHIFTY_NAVIGATIONUPDATE_H
#include "Events.h"
#include "Components/InputHandler.h"
#include "ECS/System.h"


class TabviewUpdate : System<OnUpdate>
{
    void process(const OnUpdate&) override;
};


#endif //SHIFTY_NAVIGATIONUPDATE_H
