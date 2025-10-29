#ifndef SHIFTY_COMMANDPALETTEEXPANSIONUPDATE_H
#define SHIFTY_COMMANDPALETTEEXPANSIONUPDATE_H
#include "EventBus/StandardEvents.h"
#include "ECS/System.h"


class CommandPaletteExpansionUpdate : System<OnUpdate>
{
    void process(OnUpdate&) override;
};


#endif //SHIFTY_COMMANDPALETTEEXPANSIONUPDATE_H
