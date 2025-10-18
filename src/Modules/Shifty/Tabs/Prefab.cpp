#include "Prefab.h"

#include "Components/Tab.h"
#include "Hierarchy/Systems/HierarchySystem.h"
#include "Drawing/Components/RenderTransform.h"
#include "UI/Components/Motion.h"

Entity Prefabs::createTab(const std::string& url, Entity view)
{
    Entity tab = Entity::create();
    tab.add<RenderTransform>();
    tab.add<Motion>();
    tab.add<Tab>({.url = url});
    tab.add<Hierarchy>();
    HierarchySystem::addTab(view, tab);
    return tab;
}
