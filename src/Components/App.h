#ifndef SHIFTY_SHIFTYAPP_H
#define SHIFTY_SHIFTYAPP_H

#include <SDL3/SDL.h>

#include "Layout.h"
#include "../Text.h"
#include "View.h"
#include "InputHandler.h"

namespace Shifty {
    struct App {
        SDL_Window *window;
        SDL_Renderer *renderer;
        bool running = true;

        App();

        ~App();
    };
}

#endif //SHIFTY_SHIFTYAPP_H
