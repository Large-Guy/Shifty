#ifndef SHIFTY_SHIFTYAPP_H
#define SHIFTY_SHIFTYAPP_H

#include <SDL3/SDL.h>
#include <memory>

#include "Rendering/Window.h"

struct App
{
    enum class State
    {
        Normal,
        Command,
        Tabview,
    };

    std::shared_ptr<Window> window = nullptr;

    State state = State::Normal;
    bool running = true;
};

#endif //SHIFTY_SHIFTYAPP_H
