#include "Prefabs.h"

#include "Components/Layout.h"
#include "Drawing/Components/RenderTransform.h"
#include "Components/Transform.h"

Entity Prefabs::createLayout(Layout::Type type)
{
    Entity layout = Entity::create();
    layout.add<Transform>({.wMode = Transform::Mode::Percent, .hMode = Transform::Mode::Percent, .w = 1.0f, .h = 1.0f});
    layout.add<Layout>({.type = type});
    layout.add<RenderTransform>();
    return layout;
}
