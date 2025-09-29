#ifndef SHIFTY_INPUTHANDLER_H
#define SHIFTY_INPUTHANDLER_H

#include <unordered_map>
#include <vector>
#include <functional>
#include <string>
#include <SDL3/SDL.h>

#include "EventBus.h"


struct InputHandler
{
    bool textInput;
    std::unordered_map<SDL_Keycode, bool> keyStates = {};

    bool isPressed(SDL_Keycode keycode)
    {
        return keyStates[keycode];
    }

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

struct OnMouseButtonPress
{
    InputHandler& handler;
    float x, y;
    int button;
};

struct OnMouseButtonRelease
{
    InputHandler& handler;
    float x, y;
    int button;
};

inline void InputHandler::feed(const SDL_Event* event)
{
    auto window = SDL_GetWindowFromID(event->window.windowID);
    if (textInput != SDL_TextInputActive(window))
    {
        if (textInput)
            SDL_StartTextInput(window);
        else
            SDL_StopTextInput(window);
    }
    switch (event->type)
    {
    case SDL_EVENT_KEY_DOWN:
        keyStates[event->key.key] = true;
        EventBus::emit(OnKeyPress{*this, event->key.key});
        break;
    case SDL_EVENT_KEY_UP:
        keyStates[event->key.key] = false;
        EventBus::emit(OnKeyRelease{*this, event->key.key});
        break;
    case SDL_EVENT_TEXT_INPUT:
        EventBus::emit(OnTextInput{*this, event->text.text});
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        EventBus::emit(OnMouseButtonPress{*this, event->button.x, event->button.y, event->button.button});
    case SDL_EVENT_MOUSE_BUTTON_UP:
        EventBus::emit(OnMouseButtonRelease{*this, event->button.x, event->button.y, event->button.button});
    default:
        break;
    }
}

#endif //SHIFTY_INPUTHANDLER_H
