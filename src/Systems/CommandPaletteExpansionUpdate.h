#ifndef SHIFTY_COMMANDPALETTEDRAW_H
#define SHIFTY_COMMANDPALETTEDRAW_H
#include "Events.h"
#include "Components/Draw.h"
#include "ECS/System.h"


class CommandPaletteExpansionUpdate : System<OnUpdate>
{
    void process(const OnUpdate&) override;
};


#endif //SHIFTY_COMMANDPALETTEDRAW_H
