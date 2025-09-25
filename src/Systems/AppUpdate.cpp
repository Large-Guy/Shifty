//
// Created by Ravi Lebgue on 9/24/25.
//

#include "AppUpdate.h"

#include <algorithm>

#include "../Components/App.h"

#include <SDL3/SDL.h>

namespace Shifty {
    void AppUpdate::process(const OnUpdate& _update) {
        SDL_Event e;
        ECS::Entity app = ECS::Entity::find<App>();
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_EVENT_QUIT:
                    app.get<App>().running = false;
                default:
                    break;
            }

            if (!app.has<InputHandler>())
                throw std::runtime_error("Input handler does not exist");

            app.get<InputHandler>().feed(&e);
        }
    }
} // Shifty
