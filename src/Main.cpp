#include <iostream>
#include <SDL3/SDL.h>

#include "ShiftyApp.h"

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error("SDL_Init failed");
    }

    if (!TTF_Init()) {
        throw std::runtime_error("TTF_Init failed");
    }

    auto app = ShiftyApp();
    app.run();
}
