#include <SDL3/SDL.h>

#include "ECS/Entity.h"

#include "ShiftyApp.h"
#include <iostream>

struct Vector2 {
    float x;
    float y;
};

int main(int argc, char *argv[]) {
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

    entity.add(Component::get<Vector2>());

    auto *vector2 = static_cast<Vector2 *>(entity.get(Component::get<Vector2>()));
    vector2->x = 10.0f;
    vector2->y = 20.0f;

    entity.add(Component::get<float>());
    auto *floatComponent = static_cast<float *>(entity.get(Component::get<float>()));
    *floatComponent = 10.0f;

    if (!entity.has(Component::get<Vector2>())) {
        std::cout << "Entity doesn't Vector2" << std::endl;
    } else {
        auto *vector2 = static_cast<Vector2 *>(entity.get(Component::get<Vector2>()));
        std::cout << "Entity does have Vector2: (" << vector2->x << ", " << vector2->y << ")" << std::endl;
    }
}
