#include "Prefab.h"

#include "Components/Pane.h"
#include "Drawing/TextRenderer.h"
#include "Hierarchy/Components/Hierarchy.h"
#include "Drawing/Components/RenderTransform.h"
#include "Shifty/CommandPalette/Components/CommandPalette.h"
#include "UI/Components/Animation.h"
#include "UI/Components/Edit.h"
#include "UI/Components/Layout.h"
#include "UI/Components/Selectable.h"
#include "UI/Components/Text.h"
#include "UI/Components/Transform.h"

Entity Prefabs::createView()
{
    Entity view = Entity::create();
    view.add<Transform>();
    view.add<Pane>();
    view.add<Layout>({.type = Layout::Type::FREE});
    view.add<RenderTransform>();
    view.add<Animation>({.tracks = {{"open", {}}, {"focusStart", {.speed = 2.0f}}, {"focusEnd", {.speed = 2.0f}}}});
    view.add<Selectable>();
    view.add<Hierarchy>();

    //TODO: Turn this into a prefab
    Entity commandPalette = Entity::create();
    commandPalette.add<Transform>({
        .yMode = Transform::Mode::Pixel,
        .y = 0.0f,
        .hMode = Transform::Mode::Pixel,
        .h = 32.0f
    });
    commandPalette.add<Layout>({.type = Layout::Type::FULL});
    commandPalette.add<RenderTransform>();
    commandPalette.add<CommandPalette>();
    commandPalette.add<Animation>({.tracks = {{"open", {.speed = 3.0f}}}});
    commandPalette.add<Text>({
        .text = "",
        .font = Font::load("res/fonts/Quicksand-SemiBold.ttf"),
        .size = 18
    });
    commandPalette.add<Edit>();

    Layout::addChild(view, commandPalette);

    return view;
}
