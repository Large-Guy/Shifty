//
// Created by ravilebgue on 9/27/25.
//

#ifndef SHIFTY_COMMANDPALETTEUPDATE_H
#define SHIFTY_COMMANDPALETTEUPDATE_H
#include "Events.h"
#include "ECS/System.h"


class CommandPaletteUpdate final : System<OnUpdate>
{
    void process(const OnUpdate&) override;
};


#endif //SHIFTY_COMMANDPALETTEUPDATE_H
