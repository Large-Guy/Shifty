#include "TabViewUpdate.h"

#include <iostream>
#include <ranges>

#include "GlobalConfig.h"
#include "Tween.h"
#include "Components/Animation.h"
#include "Components/Focus.h"
#include "Components/Layout.h"
#include "Components/RenderTransform.h"
#include "Components/Root.h"
#include "Components/Tab.h"
#include "Components/TabViewState.h"
#include "Components/Transform.h"
#include "Components/Panel.h"
#include "Shared/TabViewShared.h"


void TabViewUpdate::process(const OnUpdate& update)
{
    ComRef<TabViewState> viewState = Entity::find<TabViewState>();
    ComRef<Animation> viewAnimation = Entity::findEntity<TabViewState>().get<Animation>();

    //Calculate size of screen
    ComRef<RenderTransform> root = Entity::findEntity<Root>().get<RenderTransform>();
    float width = root->w;
    float height = root->h;
    if (viewState->targetView != nullptr)
    {
        width = viewState->targetView.get<RenderTransform>()->w;
        height = viewState->targetView.get<RenderTransform>()->h;
    }

    //Calculate tab size, 10% padding on either end
    float tWidth = 0.8f / GlobalConfig::tabsPerPageHorizontal * width;
    float tHeight = 0.8f / GlobalConfig::tabsPerPageVertical * height;

    float pWidth = 0.1f * width;
    float pHeight = 0.1f * height;

    int viewCount = 0;
    Entity::each<Panel>([&](ComRef<Panel> view)
    {
        viewCount++;
    });

    int i = 0;
    Entity::multiEach<Tab, RenderTransform>([&](ComRef<Tab> tab, ComRef<RenderTransform> transform)
    {
        auto viewRenderTransform = tab->viewer.get<RenderTransform>();

        int x = (i % GlobalConfig::tabsPerPageHorizontal);
        int y = i / GlobalConfig::tabsPerPageHorizontal;
        if (y > GlobalConfig::tabsPerPageVertical)
        {
            return;
        }


        float tx = static_cast<float>(x) * (tWidth) + pWidth + 8;
        float ty = static_cast<float>(y) * (tHeight) + pHeight + 8;
        if (Entity::find<TabViewState>()->targetView != nullptr)
        {
            tx += viewState->targetView.get<RenderTransform>()->x;
            ty += viewState->targetView.get<RenderTransform>()->y;
        }

        if (Entity::find<TabViewState>()->active)
        {
            float elastic = Tween::Lerp(Tween::easeInCubic(viewAnimation->time),
                                        Tween::easeOutBack(viewAnimation->time), viewAnimation->time);
            float back = Tween::easeOutBack(viewAnimation->time);

            transform->x = Tween::Lerp(viewRenderTransform->x, tx, back);
            transform->y = Tween::Lerp(viewRenderTransform->y, ty, back);
            transform->w = Tween::Lerp(viewRenderTransform->w, tWidth - 16, elastic);
            transform->h = Tween::Lerp(viewRenderTransform->h, tHeight - 16, elastic);
        }
        else
        {
            float elastic = Tween::easeInOutBack(viewAnimation->time);
            float back = Tween::Lerp(Tween::easeInOutCubic(viewAnimation->time),
                                     Tween::easeOutBack(viewAnimation->time),
                                     viewAnimation->time);

            transform->x = Tween::Lerp(tx, viewRenderTransform->x, back);
            transform->y = Tween::Lerp(ty, viewRenderTransform->y, back);
            transform->w = Tween::Lerp(tWidth - 16, viewRenderTransform->w, elastic);
            transform->h = Tween::Lerp(tHeight - 16, viewRenderTransform->h, elastic);
        }
        i++;
    });
}

