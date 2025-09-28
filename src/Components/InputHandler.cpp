#include "InputHandler.h"

#include "../EventBus.h"

bool InputHandler::isPressed(SDL_Keycode keycode)
{
    return keyStates[keycode];
}

void InputHandler::feed(const SDL_Event* event)
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
    default:



    }
}
