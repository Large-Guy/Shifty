#ifndef SHIFTY_SHIFTYAPP_H
#define SHIFTY_SHIFTYAPP_H

#include <memory>

#include "Platform/Window.h"

struct App
{
    enum class State
    {
        Normal,
        Command,
        Tabview,
    };

    std::shared_ptr<Window> window = nullptr;
    std::shared_ptr<EventHandler> handler = nullptr;

    State state = State::Normal;
    bool running = true;
};

#endif //SHIFTY_SHIFTYAPP_H
