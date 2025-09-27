#include "InputHandler.h"

#include "../EventBus.h"

bool InputHandler::isPressed(SDL_Keycode keycode) {
    return keyStates[keycode];
}

void InputHandler::feed(const SDL_Event* event) {
    switch (event->type) {
        case SDL_EVENT_KEY_DOWN:
            keyStates[event->key.key] = true;
            EventBus::emit(OnKeyPress{event->key.key});
            break;
        case SDL_EVENT_KEY_UP:
            keyStates[event->key.key] = false;
            EventBus::emit(OnKeyRelease{event->key.key});
            break;
        default:



    }
}
