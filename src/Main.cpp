#include <SDL3/SDL.h>

#include "ECS/Entity.h"
#include "EventBus.h"
#include "Events.h"

#include "ShiftyApp.h"
#include <iostream>

#include "Events.h"

using namespace Shifty;

int main(int argc, char *argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error("SDL_Init failed");
    }

    if (!TTF_Init()) {
        throw std::runtime_error("TTF_Init failed");
    }

    EventBus::subscribe<OnReady>([](const OnReady &e) {
        ECS::Entity entity = ECS::Entity::create();
        entity.add<ShiftyApp>();
    });

    EventBus::subscribe<OnUpdate>([](const OnUpdate &e) {
        ECS::Entity::each<ShiftyApp>([](ShiftyApp &app) {
            std::cout << "Update" << std::endl;
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
