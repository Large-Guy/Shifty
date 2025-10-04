//
// Created by ravilebgue on 9/28/25.
//

#ifndef SHIFTY_VIEWANIMATIONUPDATE_H
#define SHIFTY_VIEWANIMATIONUPDATE_H
#include "Events.h"
#include "ECS/System.h"


class PanelAnimationUpdate : System<OnUpdate>
{
    void process(const OnUpdate&) override;
};


#endif //SHIFTY_VIEWANIMATIONUPDATE_H
