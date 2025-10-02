//
// Created by ravilebgue on 9/27/25.
//

#ifndef SHIFTY_COMMANDPALETTEKEYDOWN_H
#define SHIFTY_COMMANDPALETTEKEYDOWN_H
#include "Components/InputHandler.h"
#include "ECS/System.h"


class CommandPaletteKeydown : System<OnKeyPress>
{
    void process(const OnKeyPress&) override;
};


#endif //SHIFTY_COMMANDPALETTEKEYDOWN_H
