#include "TabViewKeydown.h"

#include "Components/Animation.h"
#include "Components/Focus.h"
#include "Components/Layout.h"
#include "Components/TabViewState.h"
#include "Systems/Shared/TabViewShared.h"

void TabViewKeydown::process(const OnKeyPress& event)
{
    if (Entity::find<Focus>()->focused == nullptr || !Entity::find<Focus>()->focused.has<Layout>())
        return;

    bool ctrl = event.handler->isPressed(SDLK_LCTRL) || event.handler->isPressed(SDLK_RCTRL);
    bool shift = event.handler->isPressed(SDLK_LSHIFT) || event.handler->isPressed(SDLK_RSHIFT);
    if (event.key == SDLK_TAB && ctrl)
    {
        TabViewShared::show();
    }
    if (Entity::find<TabViewState>()->active && event.key == SDLK_ESCAPE)
    {
        Entity::find<TabViewState>()->active = false;
        Entity::findEntity<TabViewState>().get<Animation>()->time = 0.f;
    }
}
