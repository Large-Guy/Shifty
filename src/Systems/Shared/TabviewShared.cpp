#include "TabviewShared.h"

#include "Components/Animation.h"
#include "Components/App.h"
#include "Components/Focus.h"
#include "Components/Layout.h"
#include "Components/Panel.h"
#include "Components/RenderTransform.h"
#include "Components/Tab.h"
#include "Components/TabviewState.h"
#include "ECS/Entity.h"

void TabviewShared::show()
{
    Entity::find<App>()->state = App::State::Tabview;
    //View all tabs
    Entity::find<TabviewState>()->active = true;
    Entity::find<TabviewState>()->targetView = Entity::find<Focus>()->focused;
    Entity::find<TabviewState>()->focusedTab = Entity::find<Focus>()->focused.get<Panel>()->holdingTabs.front();
    Entity::findEntity<TabviewState>().get<Animation>()->time = 0.f;
    Entity::multiEach<Tab, RenderTransform>(
        [&](ComRef<Tab> tab, ComRef<RenderTransform> renderTransform)
        {
            auto viewRenderTransform = tab->viewer.get<RenderTransform>();
            renderTransform->x = viewRenderTransform->x;
            renderTransform->y = viewRenderTransform->y;
            renderTransform->w = viewRenderTransform->w;
            renderTransform->h = viewRenderTransform->h;
        });
}

void TabviewShared::hide()
{
    Entity::find<TabviewState>()->active = false;
    Entity::findEntity<TabviewState>().get<Animation>()->time = 0.f;
    Entity::find<App>()->state = App::State::Normal;
}

void TabviewShared::swap(Entity tab)
{
    //TODO: There is something wrong with the swapping logic. I think things are being rearranged incorrectly.
    Entity targetView = Entity::find<TabviewState>()->targetView;
    //If the view is going to be left empty, we swap tabs instead of moving them
    if (targetView.get<Panel>()->holdingTabs.size() == 1)
    {
        Panel::addTab(tab.get<Tab>()->viewer, targetView.get<Panel>()->holdingTabs.front());
    }
    Panel::addTab(targetView, tab);
    hide();
}
