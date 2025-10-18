#include "EventHandler.h"

#include "EventBus/EventBus.h"
#include "SDL3/SDL_events.h"

bool EventHandler::isPressed(SDL_Keycode keycode)
{
    return keyStates[keycode];
}

void EventHandler::pollEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        auto window = SDL_GetWindowFromEvent(&e);
        if (this->textInput != SDL_TextInputActive(window))
        {
            if (this->textInput)
                SDL_StartTextInput(window);
            else
                SDL_StopTextInput(window);
        }

        switch (e.type)
        {
        case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            EventBus::emit(OnWindowClose{window});
            break;
        case SDL_EVENT_KEY_DOWN:
            this->keyStates[e.key.key] = true;
            EventBus::emit(OnKeyPress{shared_from_this(), e.key.key});
            break;
        case SDL_EVENT_KEY_UP:
            this->keyStates[e.key.key] = false;
            EventBus::emit(OnKeyRelease{shared_from_this(), e.key.key});
            break;
        case SDL_EVENT_TEXT_INPUT:
            EventBus::emit(OnTextInput{shared_from_this(), e.text.text});
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            EventBus::emit(OnMouseButtonPress{
                shared_from_this(), e.button.x, e.button.y, e.button.button
            });
            break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
            EventBus::emit(OnMouseButtonRelease{
                shared_from_this(), e.button.x, e.button.y, e.button.button
            });
            break;
        case SDL_EVENT_WINDOW_RESIZED:
            EventBus::emit(OnWindowResize{SDL_GetWindowFromID(e.window.windowID), e.window.data1, e.window.data2});
            break;
        default:
            break;
        }
    }
}
