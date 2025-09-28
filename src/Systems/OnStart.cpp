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
#include "Components/Text.h"
#include "Components/Transform.h"
#include "Components/View.h"

void OnStart::process(const OnReady&)
{
    Entity world = Entity::create();
    world.add<InputHandler>();
    world.add<App>();
    world.add<Draw>();

    Font* font = new Font("res/fonts/hack-regular.ttf");

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
    root.add<Animation>();
    root.add<Text>({
        .text = "",
        .font = font,
        .size = 16
    });
    root.add<Edit>();
    root.add<Focus>();
}
