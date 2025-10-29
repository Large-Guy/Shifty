#include "TabviewUpdate.h"

#include <iostream>
#include <ranges>

#include "UI/Components/Animation.h"
#include "UI/Components/Layout.h"
#include "Drawing/Components/RenderTransform.h"
#include "TabviewShared.h"
#include "Config/GlobalConfig.h"
#include "Drawing/Tween.h"
#include "Hierarchy/Components/Hierarchy.h"
#include "Shifty/App/Components/App.h"
#include "Shifty/Panes/Components/Pane.h"
#include "Shifty/Panes/Components/Root.h"
#include "Shifty/Tabs/Components/Tab.h"
#include "Shifty/Tabs/Components/TabviewState.h"


void TabviewUpdate::process(OnUpdate& update)
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
    if (currentFocusedTab != Entity::null)
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
    if (viewState->targetView != Entity::null)
    {
        width = viewState->targetView.get<RenderTransform>()->w;
        height = viewState->targetView.get<RenderTransform>()->h;
    }

    //Calculate tab size, 10% padding on either end
    float tWidth = 0.8f / GlobalConfig::TabView::horizontalTabs * width;
    float tHeight = 0.8f / GlobalConfig::TabView::verticalTabs * height;

    float pWidth = 0.1f * width;
    float pHeight = 0.1f * height;

    int viewCount = 0;
    Entity::each<Pane>([&](ComRef<Pane> view)
    {
        viewCount++;
    });

    int i = 0;
    Entity::multiEach<Tab, RenderTransform, Hierarchy>(
        [&](Entity entity, ComRef<Tab> tab, ComRef<RenderTransform> transform, ComRef<Hierarchy> hierarchy)
        {
            if (i < GlobalConfig::TabView::horizontalTabs * GlobalConfig::TabView::verticalTabs * viewState->page)
            {
                i++;
                return;
            }
            auto viewRenderTransform = hierarchy->parent.get<RenderTransform>();

            int tabX = (i % GlobalConfig::TabView::horizontalTabs);
            int tabY = i / GlobalConfig::TabView::horizontalTabs;
            if (tabY >= GlobalConfig::TabView::verticalTabs)
            {
                return;
            }


            float tx = static_cast<float>(tabX) * (tWidth) + pWidth + 8;
            float ty = static_cast<float>(tabY) * (tHeight) + pHeight + 8;
            if (Entity::find<TabviewState>()->targetView != Entity::null)
            {
                tx += viewState->targetView.get<RenderTransform>()->x;
                ty += viewState->targetView.get<RenderTransform>()->y;
            }

            if (Entity::find<TabviewState>()->active)
            {
                float elastic = Tween::Lerp(Tween::easeInCubic(viewAnimation->tracks["open"].time),
                                            Tween::easeOutBack(viewAnimation->tracks["open"].time),
                                            viewAnimation->tracks["open"].time);
                float back = Tween::easeOutBack(viewAnimation->tracks["open"].time);

                transform->x = Tween::Lerp(viewRenderTransform->x, tx, back);
                transform->y = Tween::Lerp(viewRenderTransform->y, ty, back);
                transform->w = Tween::Lerp(viewRenderTransform->w, tWidth - 16, elastic);
                transform->h = Tween::Lerp(viewRenderTransform->h, tHeight - 16, elastic);
            }
            else
            {
                float elastic = Tween::easeInOutBack(viewAnimation->tracks["open"].time);
                float back = Tween::Lerp(Tween::easeInOutCubic(viewAnimation->tracks["open"].time),
                                         Tween::easeOutBack(viewAnimation->tracks["open"].time),
                                         viewAnimation->tracks["open"].time);

                float x = viewRenderTransform->x;
                float y = viewRenderTransform->y;
                float w = viewRenderTransform->w;
                float h = viewRenderTransform->h;

                x += GlobalConfig::Appearance::padding;
                y += GlobalConfig::Appearance::padding;
                w -= GlobalConfig::Appearance::padding * 2;
                h -= GlobalConfig::Appearance::padding * 2;

                transform->x = Tween::Lerp(tx, x, back);
                transform->y = Tween::Lerp(ty, y, back);
                transform->w = Tween::Lerp(tWidth - 16, w, elastic);
                transform->h = Tween::Lerp(tHeight - 16, h, elastic);
            }
            i++;
        });
}

