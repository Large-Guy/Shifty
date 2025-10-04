#include "TabviewUpdate.h"

#include <iostream>
#include <ranges>

#include "GlobalConfig.h"
#include "Tween.h"
#include "Components/Animation.h"
#include "Components/App.h"
#include "Components/Focus.h"
#include "Components/Layout.h"
#include "Components/RenderTransform.h"
#include "Components/Root.h"
#include "Components/Tab.h"
#include "Components/TabviewState.h"
#include "Components/Transform.h"
#include "Components/Panel.h"
#include "Shared/TabviewShared.h"


void TabviewUpdate::process(const OnUpdate& update)
{
    Entity viewStateEntity = Entity::findEntity<TabviewState>();
    ComRef<TabviewState> viewState = viewStateEntity.get<TabviewState>();
    ComRef<RenderTransform> viewStateTransform = viewStateEntity.get<RenderTransform>();

    ComRef<Animation> viewAnimation = Entity::findEntity<TabviewState>().get<Animation>();

    if (!viewState->active && Entity::find<App>()->state == App::State::Tabview)
    {
        Entity::find<App>()->state = App::State::Normal;
    }

    //Preview selected tag
    Entity currentFocusedTab = viewState->focusedTab;
    if (currentFocusedTab != nullptr)
    {
        ComRef<RenderTransform> currentFocusedTabTransform = currentFocusedTab.get<RenderTransform>();

        float rate = 20.f * update.deltaTime;
        viewStateTransform->x = Tween::Lerp(viewStateTransform->x, currentFocusedTabTransform->x, rate);
        viewStateTransform->y = Tween::Lerp(viewStateTransform->y, currentFocusedTabTransform->y, rate);
        viewStateTransform->w = Tween::Lerp(viewStateTransform->w, currentFocusedTabTransform->w, rate);
        viewStateTransform->h = Tween::Lerp(viewStateTransform->h, currentFocusedTabTransform->h, rate);
    }

    //Transition animation
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
        if (i < GlobalConfig::tabsPerPageHorizontal * GlobalConfig::tabsPerPageVertical * viewState->page)
        {
            i++;
            return;
        }
        auto viewRenderTransform = tab->viewer.get<RenderTransform>();

        int x = (i % GlobalConfig::tabsPerPageHorizontal);
        int y = i / GlobalConfig::tabsPerPageHorizontal;
        if (y >= GlobalConfig::tabsPerPageVertical)
        {
            return;
        }


        float tx = static_cast<float>(x) * (tWidth) + pWidth + 8;
        float ty = static_cast<float>(y) * (tHeight) + pHeight + 8;
        if (Entity::find<TabviewState>()->targetView != nullptr)
        {
            tx += viewState->targetView.get<RenderTransform>()->x;
            ty += viewState->targetView.get<RenderTransform>()->y;
        }

        if (Entity::find<TabviewState>()->active)
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

