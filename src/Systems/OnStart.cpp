#include "OnStart.h"
#include "ECS/Entity.h"
#include "Components/InputHandler.h"
#include "Components/App.h"
#include "Components/CommandPalette.h"
#include "Components/Draw.h"
#include "Components/Layout.h"
#include "Components/RenderTransform.h"
#include "Components/Transform.h"
#include "Components/View.h"

void OnStart::process(const OnReady&)
{
    Entity world = Entity::create();
    world.add<InputHandler>();
    world.add<App>();
    world.add<Draw>();

    Entity root = Entity::create();
    root.add<Transform>({
        .yMode = Transform::Mode::Pixel,
        .y = 0.0f,
        .hMode = Transform::Mode::Pixel,
        .h = 32.0f
    });
    root.add<Layout>({.type = Layout::Type::VERTICAL});
    root.add<RenderTransform>();
    root.add<CommandPalette>();
}
