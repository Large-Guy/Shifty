#include "InputHandler.h"

using namespace Shifty;

void InputHandler::EventHandler::connect(const std::function<void()>& handler) {
    handlers.push_back(handler);
}

void InputHandler::EventHandler::trigger() {
    for (const auto& handler: handlers) {
        handler();
    }
}

void InputHandler::onPressed(SDL_Keycode keycode, const std::function<void()>& handler) {
    keyEvents[keycode].onPressed.connect(handler);
}

void InputHandler::onReleased(SDL_Keycode keycode, const std::function<void()>& handler) {
    keyEvents[keycode].onPressed.connect(handler);
}

bool InputHandler::isPressed(SDL_Keycode keycode) {
    return keyStates.contains(keycode) && keyStates[keycode];
}

void InputHandler::feed(SDL_Event* event) {
    switch (event->type) {
        case SDL_EVENT_KEY_DOWN:
            keyStates[event->key.key] = true;
            if (keyEvents.contains(event->key.key)) {
                keyEvents[event->key.key].onPressed.trigger();
            }
            break;
        case SDL_EVENT_KEY_UP:
            keyStates[event->key.key] = false;
            if (keyEvents.contains(event->key.key)) {
                keyEvents[event->key.key].onReleased.trigger();
            }
            break;
        default:
            return;
    }
}