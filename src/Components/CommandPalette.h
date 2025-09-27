#ifndef SHIFTY_COMMANDPALETTE_H
#define SHIFTY_COMMANDPALETTE_H


#include <SDL3/SDL.h>
#include "Layout.h"

struct CommandPalette
{
    uint64_t lastShiftPressed = 0.0f;
    bool open;
};

#endif //SHIFTY_COMMANDPALETTE_H
