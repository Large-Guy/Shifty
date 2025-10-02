#ifndef SHIFTY_COMMANDPALETTE_H
#define SHIFTY_COMMANDPALETTE_H


#include <SDL3/SDL.h>
#include "Layout.h"
#include "Panel.h"

struct OnCommandExecute
{
    Entity view;
    std::vector<std::string> commands;
};

struct CommandPalette
{
    uint64_t lastShiftPressed = 0.0f;
    bool open = false;
};

#endif //SHIFTY_COMMANDPALETTE_H
