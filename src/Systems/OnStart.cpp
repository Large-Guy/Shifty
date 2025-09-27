#include "OnStart.h"
#include "ECS/Entity.h"
#include "Components/InputHandler.h"
#include "Components/App.h"
#include "Components/Draw.h"
#include "Components/Layout.h"
#include "Components/RenderTransform.h"
#include "Components/Transform.h"
#include "Components/View.h"

void OnStart::process(const OnReady&) {
    Entity world = Entity::create();
    world.add<InputHandler>();
    world.add<App>();
    world.add<Draw>();

    Entity testRect = Entity::create();
    testRect.add<Transform>({.x = 0.1f, .y = 0.1f, .w = 0.8f, .h = 0.8f});
    testRect.add<RenderTransform>();
    testRect.add<View>();
    testRect.add<Layout>();
}