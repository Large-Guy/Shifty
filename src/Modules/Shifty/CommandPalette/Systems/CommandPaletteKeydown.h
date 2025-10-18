#ifndef SHIFTY_COMMANDPALETTEKEYDOWN_H
#define SHIFTY_COMMANDPALETTEKEYDOWN_H
#include "Platform/EventHandler.h"
#include "ECS/System.h"

class CommandPaletteKeydown : System<OnKeyPress>
{
    void process(const OnKeyPress&) override;
};


#endif //SHIFTY_COMMANDPALETTEKEYDOWN_H
