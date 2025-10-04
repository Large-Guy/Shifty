#ifndef SHIFTY_SHIFTYAPP_H
#define SHIFTY_SHIFTYAPP_H

#include <SDL3/SDL.h>

struct App
{
    enum class State
    {
        Normal,
        Command,
        Tabview,
    };

    State state = State::Normal;
    SDL_Window* window;
    bool running = true;
};

#endif //SHIFTY_SHIFTYAPP_H
