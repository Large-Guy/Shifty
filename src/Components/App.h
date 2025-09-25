#ifndef SHIFTY_SHIFTYAPP_H
#define SHIFTY_SHIFTYAPP_H

#include <SDL3/SDL.h>

struct App {
    SDL_Window *window;
    bool running = true;

    App();

    ~App();
};

#endif //SHIFTY_SHIFTYAPP_H
