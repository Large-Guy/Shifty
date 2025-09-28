#include "OnStart.h"

#include "Components/Animation.h"
#include "ECS/Entity.h"
#include "Components/InputHandler.h"
#include "Components/App.h"
#include "Components/CommandPalette.h"
#include "Components/Draw.h"
#include "Components/Edit.h"
#include "Components/Focus.h"
#include "Components/Layout.h"
#include "Components/RenderTransform.h"
#include "Components/Root.h"
#include "Components/Text.h"
#include "Components/Transform.h"
#include "Components/View.h"

void OnStart::process(const OnReady&)
{
    Entity world = Entity::create();
    world.add<InputHandler>();
    world.add<App>();
    world.add<Draw>();

    Entity commandPalette = Entity::create();
    commandPalette.add<Transform>({
        .yMode = Transform::Mode::Pixel,
        .y = 0.0f,
        .hMode = Transform::Mode::Pixel,
        .h = 32.0f
    });
    commandPalette.add<Layout>({.type = Layout::Type::VERTICAL});
    commandPalette.add<RenderTransform>();
    commandPalette.add<CommandPalette>();
    commandPalette.add<Animation>();
    commandPalette.add<Text>({
        .text = "",
        .font = Font::load("res/fonts/hack-regular.ttf"),
        .size = 15
    });
    commandPalette.add<Edit>();
    commandPalette.add<Focus>();

    Entity layoutRoot = Entity::create();
    layoutRoot.add<Transform>();
    layoutRoot.add<Layout>();
    layoutRoot.add<RenderTransform>();
    layoutRoot.add<Root>();
}
