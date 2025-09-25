#include "OnStart.h"
#include "../ECS/Entity.h"
#include "../Components/InputHandler.h"
#include "../Components/App.h"
#include "../Components/Draw.h"
#include "../Components/Layout.h"

void OnStart::process(const OnReady&) {
    Entity world = Entity::create();
    world.add<InputHandler>();
    world.add<App>();
    world.add<Draw>();

    Entity testRect = Entity::create();
    testRect.add<SDL_FRect>({0, 0, 100, 100});
    testRect.add<SDL_Color>({255, 255, 255});
}
