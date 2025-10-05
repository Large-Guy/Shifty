#include "OnStart.h"

#include "Prefabs.h"
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
#include "Components/TabviewState.h"
#include "Components/Text.h"
#include "Components/Transform.h"
#include "Components/Panel.h"

void OnStart::process(const OnReady&)
{
    Entity world = Entity::create();
    world.add<InputHandler>();
    world.add<App>();
    world.add<Draw>();
    world.add<Focus>();

    Entity layoutRoot = Prefabs::createLayout(Layout::Type::FULL);
    layoutRoot.add<Root>();

    Entity mainView = Prefabs::createView();

    Layout::addChild(layoutRoot, mainView);

    Entity tabViewState = Entity::create();
    tabViewState.add<TabviewState>();
    tabViewState.add<Animation>({.speed = 2.f});
    tabViewState.add<RenderTransform>();

    world.get<Focus>()->focused = mainView;
}
