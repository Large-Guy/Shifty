#ifndef SHIFTY_INPUTHANDLER_H
#define SHIFTY_INPUTHANDLER_H

#include <unordered_map>
#include <vector>
#include <functional>
#include <SDL3/SDL.h>

namespace Shifty {
    struct OnKeyPress {
        SDL_Keycode key;
    };

    struct OnKeyRelease {
        SDL_Keycode key;
    };

    struct InputHandler {
        std::unordered_map<SDL_Keycode, bool> keyStates = {};

        bool isPressed(SDL_Keycode keycode);

        void feed(const SDL_Event* event);
    };
}


#endif //SHIFTY_INPUTHANDLER_H
