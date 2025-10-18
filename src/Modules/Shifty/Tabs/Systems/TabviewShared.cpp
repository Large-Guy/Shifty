
#include "TabviewShared.h"

#include "UI/Components/Animation.h"
#include "Drawing/Components/RenderTransform.h"
#include "ECS/Entity.h"
#include "Hierarchy/Components/Hierarchy.h"
#include "Hierarchy/Systems/HierarchySystem.h"
#include "Shifty/App/Components/App.h"
#include "Shifty/Panes/Components/Pane.h"
#include "Shifty/Tabs/Components/Tab.h"
#include "Shifty/Tabs/Components/TabviewState.h"
#include "UI/Components/Focus.h"

void TabviewShared::show()
{
    Entity::find<App>()->state = App::State::Tabview;
    //View all tabs
    Entity::find<TabviewState>()->active = true;
    Entity::find<TabviewState>()->targetView = Entity::find<Focus>()->focused;
    Entity::find<TabviewState>()->focusedTab = Entity::find<Focus>()->focused.get<Hierarchy>()->children.front();
    Entity::findEntity<TabviewState>().get<Animation>()->tracks["open"].time = 0.f;
    Entity::multiEach<Tab, RenderTransform, Hierarchy>(
        [&](ComRef<Tab> tab, ComRef<RenderTransform> renderTransform, ComRef<Hierarchy> hierarchy)
        {
            auto viewRenderTransform = hierarchy->parent.get<RenderTransform>();
            renderTransform->x = viewRenderTransform->x;
            renderTransform->y = viewRenderTransform->y;
            renderTransform->w = viewRenderTransform->w;
            renderTransform->h = viewRenderTransform->h;
        });
}

void TabviewShared::hide()
{
    Entity::find<TabviewState>()->active = false;
    Entity::findEntity<TabviewState>().get<Animation>()->tracks["open"].time = 0.f;
    Entity::find<App>()->state = App::State::Normal;
}

void TabviewShared::swap(Entity tab)
{
    //TODO: There is something wrong with the swapping logic. I think things are being rearranged incorrectly.
    Entity targetView = Entity::find<TabviewState>()->targetView;
    //If the view is going to be left empty, we swap tabs instead of moving them
    if (targetView.get<Hierarchy>()->children.size() == 1)
    {
        HierarchySystem::addTab(tab.get<Hierarchy>()->parent, targetView.get<Hierarchy>()->children.front());
    }
    HierarchySystem::addTab(targetView, tab);
    hide();
}
