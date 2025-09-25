#include "OnStart.h"
#include "../ECS/Entity.h"
#include "../Components/InputHandler.h"
#include "../Components/App.h"
#include "../Components/Draw.h"

void OnStart::process(const OnReady&) {
    Entity world = Entity::create();
    world.add<InputHandler>();
    world.add<App>();
    world.add<Draw>();

    /*
    Entity root = Entity::create();
    root.add<Layout>();
    root.add<View>();
    root.add<CommandPalette>();
    */
}
