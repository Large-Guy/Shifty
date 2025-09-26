//
// Created by Ravi Lebgue on 9/24/25.
//

#include "AppUpdate.h"

#include <stdexcept>


#include "../Components/App.h"
#include "../ECS/Entity.h"
#include "../Components/InputHandler.h"

#include <SDL3/SDL.h>

#include "RenderTransformsCompute.h"

void AppUpdate::process(const OnUpdate& _update) {
    SDL_Event e;
    Entity app = Entity::find<App>();
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

    int screenWidth, screenHeight;
    SDL_GetWindowSize(app.get<App>().window, &screenWidth, &screenHeight);

    EventBus::emit<OnLayout>({static_cast<float>(screenWidth), static_cast<float>(screenHeight)});
}
