#include <SDL3/SDL.h>

#include "ECS/Entity.h"
#include "EventBus.h"
#include "Events.h"

#include "ShiftyApp.h"
#include <SDL3/SDL.h>
#include <iostream>

#include "CommandPalette.h"
#include "Events.h"

using namespace Shifty;

int main(int argc, char *argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error("SDL_Init failed");
    }

    if (!TTF_Init()) {
        throw std::runtime_error("TTF_Init failed");
    }

    ECS::Entity world = ECS::Entity::create();
    world.add<InputHandler>();
    world.add<ShiftyApp>();

    EventBus::subscribe<OnReady>([](const OnReady &e) {
        ECS::Entity root = ECS::Entity::create();
        root.add<Layout>();
        root.add<View>();
        root.add<CommandPalette>();
    });

    EventBus::subscribe<OnUpdate>([&](const OnUpdate &event) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_EVENT_QUIT:
                    world.get<ShiftyApp>().running = false;
                default:
                    break;
            }

            if (!world.has<InputHandler>())
                throw std::runtime_error("Input handler does not exist");

            world.get<InputHandler>().feed(&e);
        }
    });

    EventBus::subscribe<OnRender>([](const OnRender &e) {
        ECS::Entity::each<ShiftyApp>([](ShiftyApp &app) {
            SDL_RenderClear(app.renderer);
            SDL_RenderPresent(app.renderer);
        });

        ECS::Entity::each<CommandPalette>([](ECS::Entity entity, CommandPalette &view) {
            if (view.open) {
                auto &layout = entity.get<Layout>();
            }
        });
    });

    EventBus::emit(OnReady{});

    while (world.get<ShiftyApp>().running) {
        EventBus::emit(OnUpdate{
            0.016f
        });
        EventBus::emit(OnRender{});
    }
}
