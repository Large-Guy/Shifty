#ifndef SHIFTY_INPUTHANDLER_H
#define SHIFTY_INPUTHANDLER_H

#include <unordered_map>
#include <vector>
#include <functional>
#include <SDL3/SDL.h>

namespace Shifty {

    class InputHandler {
    private:
        class EventHandler {
        private:
            std::vector<std::function<void()>> handlers = {};
        public:
            void connect(const std::function<void()>& handler);

            void trigger();
        };

        struct KeyEventHandler {
            EventHandler onPressed = {};
            EventHandler onReleased = {};
        };

        std::unordered_map<SDL_Keycode, bool> keyStates = {};
        std::unordered_map<SDL_Keycode, KeyEventHandler> keyEvents = {};
    public:
        void onPressed(SDL_Keycode keycode, const std::function<void()>& handler);

        void onReleased(SDL_Keycode keycode, const std::function<void()>& handler);

        bool isPressed(SDL_Keycode keycode);

        void feed(SDL_Event* event);
    };

}


#endif //SHIFTY_INPUTHANDLER_H
