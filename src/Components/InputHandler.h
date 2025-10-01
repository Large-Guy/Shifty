#ifndef SHIFTY_INPUTHANDLER_H
#define SHIFTY_INPUTHANDLER_H

#include <unordered_map>
#include <vector>
#include <functional>
#include <string>
#include <SDL3/SDL.h>

#include "EventBus.h"
#include "ECS/Entity.h"


struct InputHandler
{
    bool textInput;
    std::unordered_map<SDL_Keycode, bool> keyStates = {};

    bool isPressed(SDL_Keycode keycode)
    {
        return keyStates[keycode];
    }
};

struct OnKeyPress
{
    ComRef<InputHandler> handler;
    SDL_Keycode key;
};

struct OnKeyRelease
{
    ComRef<InputHandler> handler;
    SDL_Keycode key;
};

struct OnTextInput
{
    ComRef<InputHandler> handler;
    const std::string& input;
};

struct OnMouseButtonPress
{
    ComRef<InputHandler> handler;
    float x, y;
    int button;
};

struct OnMouseButtonRelease
{
    ComRef<InputHandler> handler;
    float x, y;
    int button;
};

#endif //SHIFTY_INPUTHANDLER_H
