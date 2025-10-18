#ifndef SHIFTY_COMMANDPALETTEUPDATE_H
#define SHIFTY_COMMANDPALETTEUPDATE_H
#include "EventBus/StandardEvents.h"
#include "ECS/System.h"

class CommandPaletteUpdate final : System<OnUpdate>
{
    void process(const OnUpdate&) override;
};


#endif //SHIFTY_COMMANDPALETTEUPDATE_H
