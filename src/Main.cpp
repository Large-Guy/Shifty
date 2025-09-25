#include <SDL3/SDL.h>

#include "ECS/Entity.h"
#include "EventBus.h"
#include "Events.h"

#include "Components/App.h"
#include <iostream>

#include "Components/CommandPalette.h"
#include "Events.h"
#include "Systems/AppUpdate.h"

int main(int argc, char *argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error("SDL_Init failed");
    }

    if (!TTF_Init()) {
        throw std::runtime_error("TTF_Init failed");
    }

    Entity world = Entity::create();
    world.add<InputHandler>();
    world.add<App>();

    AppUpdate appUpdate{};

    EventBus::subscribe<OnReady>([](const OnReady &e) {
        Entity root = Entity::create();
        root.add<Layout>();
        root.add<View>();
        root.add<CommandPalette>();
    });

    EventBus::subscribe<OnRender>([](const OnRender &e) {
        Entity::each<App>([](App &app) {
            SDL_RenderClear(app.renderer);
            SDL_RenderPresent(app.renderer);
        });

        Entity::each<CommandPalette>([](Entity entity, CommandPalette &view) {
            if (view.open) {
                auto &layout = entity.get<Layout>();
            }
        });
    });

    EventBus::emit(OnReady{});

    while (world.get<App>().running) {
        EventBus::emit(OnUpdate{
            0.016f
        });
        EventBus::emit(OnRender{});
    }
}
