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
}
