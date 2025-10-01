#include "TabViewSystems.h"

#include <iostream>

#include "GlobalConfig.h"
#include "Tween.h"
#include "Components/Animation.h"
#include "Components/Focus.h"
#include "Components/Layout.h"
#include "Components/RenderTransform.h"
#include "Components/Root.h"
#include "Components/TabViewState.h"
#include "Components/Transform.h"
#include "Components/View.h"

void TabViewKeydown::process(const OnKeyPress& event)
{
    bool ctrl = event.handler->isPressed(SDLK_LCTRL) || event.handler->isPressed(SDLK_RCTRL);
    bool shift = event.handler->isPressed(SDLK_LSHIFT) || event.handler->isPressed(SDLK_RSHIFT);
    if (event.key == SDLK_TAB && ctrl)
    {
        Entity::find<TabViewState>()->active = true;
        Entity::findEntity<TabViewState>().get<Animation>()->time = 0.f;
        Entity::multiEach<View, RenderTransform>(
            [&](ComRef<View> view, ComRef<RenderTransform> renderTransform)
            {
                renderTransform->overrideX = true;
                renderTransform->overrideY = true;
                renderTransform->overrideW = true;
                renderTransform->overrideH = true;
                renderTransform->overriddenX = renderTransform->x;
                renderTransform->overriddenY = renderTransform->y;
                renderTransform->overriddenW = renderTransform->w;
                renderTransform->overriddenH = renderTransform->h;
            });
    }
    if (Entity::find<TabViewState>()->active && event.key == SDLK_ESCAPE)
    {
        Entity::find<TabViewState>()->active = false;
        Entity::findEntity<TabViewState>().get<Animation>()->time = 0.f;
    }
}

void TabViewUpdate::process(const OnUpdate& update)
{
    ComRef<Animation> viewAnimation = Entity::findEntity<TabViewState>().get<Animation>();

    //Calculate size of screen
    Entity browserDisplay = Entity::findEntity<Root>();
    float width = browserDisplay.get<RenderTransform>()->w;
    float height = browserDisplay.get<RenderTransform>()->h;

    //Calculate tab size, 10% padding on either end
    float tWidth = 0.8f / GlobalConfig::tabsPerPageHorizontal * width;
    float tHeight = 0.8f / GlobalConfig::tabsPerPageVertical * height;

    float pWidth = 0.1f * width;
    float pHeight = 0.1f * height;

    int viewCount = 0;
    Entity::each<View>([&](ComRef<View> view)
    {
        viewCount++;
    });

    int i = 0;
    Entity::multiEach<View, RenderTransform>([&](ComRef<View> view, ComRef<RenderTransform> transform)
    {
        int x = (i % GlobalConfig::tabsPerPageHorizontal);
        int y = i / GlobalConfig::tabsPerPageHorizontal;
        if (y > GlobalConfig::tabsPerPageVertical)
        {
            return;
        }


        float tx = static_cast<float>(x) * (tWidth) + pWidth;
        float ty = static_cast<float>(y) * (tHeight) + pHeight;

        if (Entity::find<TabViewState>()->active)
        {
            float elastic = Tween::Lerp(Tween::easeInCubic(viewAnimation->time),
                                        Tween::easeOutBack(viewAnimation->time), viewAnimation->time);
            float back = Tween::easeOutBack(viewAnimation->time);

            transform->overriddenX = Tween::Lerp(transform->x, tx, back);
            transform->overriddenY = Tween::Lerp(transform->y, ty, back);
            transform->overriddenW = Tween::Lerp(transform->w, tWidth, elastic);
            transform->overriddenH = Tween::Lerp(transform->h, tHeight, elastic);
        }
        else
        {
            float elastic = Tween::easeInOutBack(viewAnimation->time);
            float back = Tween::Lerp(Tween::easeInOutCubic(viewAnimation->time),
                                     Tween::easeOutBack(viewAnimation->time),
                                     viewAnimation->time);

            transform->overriddenX = Tween::Lerp(tx, transform->x, back);
            transform->overriddenY = Tween::Lerp(ty, transform->y, back);
            transform->overriddenW = Tween::Lerp(tWidth, transform->w, elastic);
            transform->overriddenH = Tween::Lerp(tHeight, transform->h, elastic);
        }
        i++;
    });
}
