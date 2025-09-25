#ifndef SHIFTY_COMMANDPALETTE_H
#define SHIFTY_COMMANDPALETTE_H


#include <SDL3/SDL.h>
#include "Layout.h"

struct CommandPalette {
    bool open = false;
    float openTime = 0;
};

#endif //SHIFTY_COMMANDPALETTE_H
