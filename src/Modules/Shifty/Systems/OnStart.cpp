#include "OnStart.h"

#include "UI/Components/Animation.h"
#include "ECS/Entity.h"
#include "Platform/EventHandler.h"
#include "Drawing/Components/Draw.h"
#include "UI/Components/Focus.h"
#include "UI/Components/Layout.h"
#include "Drawing/Components/RenderTransform.h"
#include "Shifty/App/Components/App.h"
#include "Shifty/Panes/Components/Root.h"
#include "UI/Prefabs.h"
#include "Shifty/Panes/Prefab.h"
#include "Shifty/Tabs/Prefab.h"
#include "Shifty/Tabs/Components/TabviewState.h"

void OnStart::process(OnReady&)
{
    Entity world = Entity::create();
    world.add<App>();
    world.add<Draw>();
    world.add<Focus>();
    world.add<Animation>();

    Entity layoutRoot = Prefabs::createLayout(Layout::Type::FULL);
    layoutRoot.add<Root>();

    Entity mainView = Prefabs::createView();
    Entity mainTab = Prefabs::createTab("test", mainView);

    Layout::addChild(layoutRoot, mainView);

    Entity tabViewState = Entity::create();
    tabViewState.add<TabviewState>();
    tabViewState.add<Animation>({.tracks = {{"open", {.speed = 2.f}}}});
    tabViewState.add<RenderTransform>();

    world.get<Focus>()->focused = mainView;
}
