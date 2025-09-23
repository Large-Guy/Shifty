#include <SDL3/SDL.h>

#include "ECS/Entity.h"
#include "EventBus.h"
#include "Events.h"

#include "ShiftyApp.h"
#include <SDL3/SDL.h>
#include <iostream>

#include "Events.h"

using namespace Shifty;

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error("SDL_Init failed");
    }

    if (!TTF_Init()) {
        throw std::runtime_error("TTF_Init failed");
    }

    ECS::Entity world = ECS::Entity::create();
    world.add<InputHandler>();

    EventBus::subscribe<OnReady>([](const OnReady& e) {
        ECS::Entity entity = ECS::Entity::create();
        entity.add<ShiftyApp>();
    });

    EventBus::subscribe<OnUpdate>([&](const OnUpdate& event) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_EVENT_QUIT:
                    exit(0);
                    break;
                default:
                    break;
            }

            if (!world.has<InputHandler>())
                throw std::runtime_error("Input handler does not exist");

            world.get<InputHandler>().feed(&e);
        }
    });

    EventBus::subscribe<OnUpdate>([](const OnUpdate& e) {
        ECS::Entity::each<ShiftyApp>([](ShiftyApp& app) {
            app.update();
        });
    });

    EventBus::subscribe<OnRender>([](const OnRender& e) {
        ECS::Entity::each<ShiftyApp>([](ShiftyApp& app) {
            app.render();
        });
    });

    EventBus::emit(OnReady{});

    while (true) {
        EventBus::emit(OnUpdate{
            0.016f
        });
        EventBus::emit(OnRender{});
    }
}
