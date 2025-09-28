#ifndef SHIFTY_INPUTHANDLER_H
#define SHIFTY_INPUTHANDLER_H

#include <unordered_map>
#include <vector>
#include <functional>
#include <string>
#include <SDL3/SDL.h>


struct InputHandler
{
    bool textInput;
    std::unordered_map<SDL_Keycode, bool> keyStates = {};

    bool isPressed(SDL_Keycode keycode);

    void feed(const SDL_Event* event);
};

struct OnKeyPress
{
    InputHandler& handler;
    SDL_Keycode key;
};

struct OnKeyRelease
{
    InputHandler& handler;
    SDL_Keycode key;
};

struct OnTextInput
{
    InputHandler& handler;
    const std::string& input;
};

#endif //SHIFTY_INPUTHANDLER_H
