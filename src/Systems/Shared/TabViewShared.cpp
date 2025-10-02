#include "TabViewShared.h"

#include "Components/Animation.h"
#include "Components/Focus.h"
#include "Components/RenderTransform.h"
#include "Components/Tab.h"
#include "Components/TabViewState.h"
#include "ECS/Entity.h"

void TabViewShared::show()
{
    //View all tabs
    Entity::find<TabViewState>()->active = true;
    Entity::find<TabViewState>()->targetView = Entity::find<Focus>()->focused;
    Entity::findEntity<TabViewState>().get<Animation>()->time = 0.f;
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
