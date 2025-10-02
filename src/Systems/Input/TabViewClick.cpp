#include "TabViewClick.h"

#include "Components/Animation.h"
#include "Components/Panel.h"
#include "Components/RenderTransform.h"
#include "Components/Tab.h"
#include "Components/TabViewState.h"

void TabViewClick::process(const OnMouseButtonPress& press)
{
    if (!Entity::find<TabViewState>()->active)
        return;

    if (press.button != SDL_BUTTON_LEFT)
        return;

    Entity::multiEach<Tab, RenderTransform>([&](Entity entity, ComRef<Tab> tab, ComRef<RenderTransform> transform)
    {
        if (transform->x < press.x && transform->x + transform->w > press.x &&
            transform->y < press.y && transform->y + transform->h > press.y)
        {
            Entity targetView = Entity::find<TabViewState>()->targetView;
            //If the view is going to be left empty, we swap tabs instead of moving them
            if (targetView.get<Panel>()->holdingTabs.size() == 1)
            {
                Panel::addTab(entity.get<Tab>()->viewer, targetView.get<Panel>()->holdingTabs.front());
            }
            Panel::addTab(targetView, entity);
            Entity::find<TabViewState>()->active = false;
            Entity::findEntity<TabViewState>().get<Animation>()->time = 0.0f;
        }
    });
}
