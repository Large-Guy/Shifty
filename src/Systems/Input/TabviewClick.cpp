#include "TabviewClick.h"

#include "Components/Animation.h"
#include "Components/Panel.h"
#include "Components/RenderTransform.h"
#include "Components/Tab.h"
#include "Components/TabviewState.h"
#include "Systems/Shared/TabviewShared.h"

void TabviewClick::process(const OnMouseButtonPress& press)
{
    if (!Entity::find<TabviewState>()->active)
        return;

    if (press.button != SDL_BUTTON_LEFT)
        return;

    Entity::multiEach<Tab, RenderTransform>([&](Entity entity, ComRef<Tab> tab, ComRef<RenderTransform> transform)
    {
        if (transform->x < press.x && transform->x + transform->w > press.x &&
            transform->y < press.y && transform->y + transform->h > press.y)
        {
            TabviewShared::swap(entity);
        }
    });
}
