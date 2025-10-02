#include "TabViewSystems.h"

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
#include "Components/View.h"

void TabViewKeydown::process(const OnKeyPress& event)
{
    if (Entity::find<Focus>()->focused == nullptr || !Entity::find<Focus>()->focused.has<Layout>())
        return;

    bool ctrl = event.handler->isPressed(SDLK_LCTRL) || event.handler->isPressed(SDLK_RCTRL);
    bool shift = event.handler->isPressed(SDLK_LSHIFT) || event.handler->isPressed(SDLK_RSHIFT);
    if (event.key == SDLK_TAB && ctrl)
    {
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
    if (Entity::find<TabViewState>()->active && event.key == SDLK_ESCAPE)
    {
        Entity::find<TabViewState>()->active = false;
        Entity::findEntity<TabViewState>().get<Animation>()->time = 0.f;
    }
}

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
    Entity::each<View>([&](ComRef<View> view)
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
            if (targetView.get<View>()->holdingTabs.size() == 1)
            {
                View::addTab(entity.get<Tab>()->viewer, targetView.get<View>()->holdingTabs.front());
            }
            View::addTab(targetView, entity);
            Entity::find<TabViewState>()->active = false;
            Entity::findEntity<TabViewState>().get<Animation>()->time = 0.0f;
        }
    });
}
