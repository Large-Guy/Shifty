#include "Prefabs.h"

#include <iostream>

#include "Components/Animation.h"
#include "Components/CommandPalette.h"
#include "Components/Edit.h"
#include "Components/Focus.h"
#include "Components/Layout.h"
#include "Components/Motion.h"
#include "Components/RenderTransform.h"
#include "Components/Selectable.h"
#include "Components/Tab.h"
#include "Components/Text.h"
#include "Components/Transform.h"
#include "Components/Panel.h"

Entity Prefabs::createView()
{
    Entity view = Entity::create();
    view.add<Transform>();
    view.add<Panel>();
    view.add<Layout>({.type = Layout::Type::FREE});
    view.add<RenderTransform>();
    view.add<Animation>({.tracks = {{"open", {}}}});
    view.add<Selectable>();

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

    createTab("Test", view);

    return view;
}

Entity Prefabs::createLayout(Layout::Type type)
{
    Entity layout = Entity::create();
    layout.add<Transform>({.wMode = Transform::Mode::Percent, .hMode = Transform::Mode::Percent, .w = 1.0f, .h = 1.0f});
    layout.add<Layout>({.type = type});
    layout.add<RenderTransform>();
    return layout;
}

Entity Prefabs::createTab(const std::string& url, Entity view)
{
    Entity tab = Entity::create();
    tab.add<RenderTransform>();
    tab.add<Motion>();
    tab.add<Tab>({.url = url});
    Panel::addTab(view, tab);
    return tab;
}
