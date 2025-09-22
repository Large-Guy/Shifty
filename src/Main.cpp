#include <SDL3/SDL.h>

#include "ECS/Entity.h"

#include "ShiftyApp.h"
#include <iostream>

float test(float a) {
    std::cout << "Test ran" << std::endl;
    return a * 2;
}

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error("SDL_Init failed");
    }

    if (!TTF_Init()) {
        throw std::runtime_error("TTF_Init failed");
    }

    auto app = Shifty::ShiftyApp();
    //app.run();

    using namespace Shifty::ECS;

    Entity entity = Entity::create();

    entity.add(1);
    entity.add(2);

    if (!entity.has(1)) {
        std::cout << "Entity doesn't have 1" << std::endl;
    } else {
        std::cout << "Entity does have 1" << std::endl;
    }
}
