#ifndef SHIFTY_SHIFTYAPP_H
#define SHIFTY_SHIFTYAPP_H

#include <SDL3/SDL.h>

#include "Layout.h"
#include "Text.h"
#include "View.h"
#include "InputHandler.h"

namespace Shifty {
    struct ShiftyApp {
        SDL_Window *window;
        SDL_Renderer *renderer;
        bool running = true;

        ShiftyApp();

        ~ShiftyApp();
    };
}

#endif //SHIFTY_SHIFTYAPP_H
