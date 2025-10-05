#include "TabviewKeydown.h"

#include <iostream>

#include "GlobalConfig.h"
#include "Components/Animation.h"
#include "Components/App.h"
#include "Components/Focus.h"
#include "Components/Layout.h"
#include "Components/Tab.h"
#include "Components/TabviewState.h"
#include "Systems/Shared/TabviewShared.h"

void TabviewKeydown::process(const OnKeyPress& event)
{
    if (Entity::find<Focus>()->focused == Entity::null || !Entity::find<Focus>()->focused.has<Layout>())
        return;

    bool ctrl = event.handler->isPressed(SDLK_LCTRL) || event.handler->isPressed(SDLK_RCTRL);
    bool shift = event.handler->isPressed(SDLK_LSHIFT) || event.handler->isPressed(SDLK_RSHIFT);
    if (event.key == SDLK_TAB && ctrl && Entity::find<App>()->state == App::State::Normal)
    {
        TabviewShared::show();
    }

    if (Entity::find<App>()->state != App::State::Tabview || !Entity::find<TabviewState>()->active)
        return;

    if (event.key == SDLK_ESCAPE)
    {
        TabviewShared::hide();
    }

    if (event.key == SDLK_RETURN)
    {
        TabviewShared::swap(Entity::find<TabviewState>()->focusedTab);
    }

    int x = 0, y = 0;

    if (event.key == SDLK_LEFT)
    {
        x--;
    }
    if (event.key == SDLK_RIGHT)
    {
        x++;
    }
    if (event.key == SDLK_UP)
    {
        y--;
    }
    if (event.key == SDLK_DOWN)
    {
        y++;
    }

    if (x != 0 || y != 0)
    {
        //Move
        int currentIndex = 0;
        std::vector<Entity> tabs;
        Entity::each<Tab>([&](Entity entity, ComRef<Tab>)
        {
            if (entity == Entity::find<TabviewState>()->focusedTab)
                currentIndex = tabs.size();
            tabs.push_back(entity);
        });

        int currentX = currentIndex % GlobalConfig::tabsPerPageHorizontal;
        int currentY = currentIndex / GlobalConfig::tabsPerPageHorizontal;

        currentX += x;

        //Calculate number of tabs in current row
        int columns = tabs.size() - currentY * GlobalConfig::tabsPerPageHorizontal;
        if (columns > GlobalConfig::tabsPerPageHorizontal)
            columns = GlobalConfig::tabsPerPageHorizontal;

        if (currentX < 0 || currentX >= columns)
            currentX -= x;

        currentY += y;

        int rows = (tabs.size() + 3) / GlobalConfig::tabsPerPageHorizontal;

        if (currentY < 0 || currentY >= rows)
            currentY -= y;

        currentIndex = currentY * GlobalConfig::tabsPerPageHorizontal + currentX;

        if (currentIndex >= tabs.size())
            currentIndex = tabs.size() - 1;
        if (currentIndex < 0)
            currentIndex = 0;

        Entity::find<TabviewState>()->focusedTab = tabs[currentIndex];
    }
}
