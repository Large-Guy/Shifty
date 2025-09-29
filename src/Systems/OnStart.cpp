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
#include "Components/Text.h"
#include "Components/Transform.h"
#include "Components/View.h"

void OnStart::process(const OnReady&)
{
    Entity world = Entity::create();
    world.add<InputHandler>();
    world.add<App>();
    world.add<Draw>();
    world.add<Focus>();

    Entity layoutRoot = Prefabs::createLayout(Layout::Type::FULL);
    layoutRoot.add<Root>();

    Layout::addChild(layoutRoot, Prefabs::createView());
}
