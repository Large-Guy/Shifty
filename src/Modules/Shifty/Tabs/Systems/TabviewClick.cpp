#include "TabviewClick.h"

#include <SDL3/SDL_mouse.h>

#include "TabviewShared.h"
#include "Drawing/Components/RenderTransform.h"
#include "ECS/Entity.h"
#include "Shifty/Tabs/Components/Tab.h"
#include "Shifty/Tabs/Components/TabviewState.h"

void TabviewClick::process(OnMouseButtonPress& press)
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
