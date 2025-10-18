#ifndef SHIFTY_COMMANDPALETTE_H
#define SHIFTY_COMMANDPALETTE_H

#include "UI/Components/Layout.h"

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
