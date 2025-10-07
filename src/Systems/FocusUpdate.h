//
// Created by ravilebgue on 10/6/25.
//

#ifndef SHIFTY_FOCUSUPDATE_H
#define SHIFTY_FOCUSUPDATE_H
#include "Events.h"
#include "ECS/System.h"


class FocusUpdate : System<OnUpdate>
{
    void process(const OnUpdate&) override;
};


#endif //SHIFTY_FOCUSUPDATE_H
