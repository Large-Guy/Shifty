#include "TabCommand.h"

#include <iostream>

#include "UI/Components/Animation.h"
#include "UI/Components/Focus.h"
#include "Drawing/Components/RenderTransform.h"
#include "Shifty/Tabs/Systems/TabviewShared.h"
#include "Shifty/Panes/Prefab.h"
#include "Shifty/Tabs/Prefab.h"
#include "UI/Prefabs.h"

static void split(Layout::Type type, Entity view)
{
    if (view.get<Layout>()->parent != Entity::null)
    {
        auto parentLayout = view.get<Layout>()->parent.get<Layout>();
        //Find my index
        auto myIndexIter = std::find(parentLayout->children.begin(), parentLayout->children.end(), view);
        size_t myIndex = std::distance(parentLayout->children.begin(), myIndexIter);
        Entity newView = Prefabs::createView();
        Entity newTab = Prefabs::createTab("test", newView);
        if (parentLayout->type == type)
        {
            Layout::addChild(view.get<Layout>()->parent, newView);
        }
        else
        {
            Entity newLayout = Prefabs::createLayout(type);
            Layout::insertChild(view.get<Layout>()->parent, newLayout, myIndex);
            Layout::addChild(newLayout, view);
            Layout::addChild(newLayout, newView);
            Entity::find<Focus>()->focused = newView;
        }
    }
    else
    {
        throw std::runtime_error("No parent layout");
    }
}

void TabCommand::process(OnCommandExecute& command)
{
    if (command.commands.empty())
        return;

    if (command.commands.front() == ":split" || command.commands.front() == ":sp")
    {
        command.consumed = true;
        //Splits the panel the long way
        auto transform = command.view.get<RenderTransform>();

        //Determine the long way
        if (transform->w > transform->h)
        {
            split(Layout::Type::HORIZONTAL, command.view);
        }
        else
        {
            split(Layout::Type::VERTICAL, command.view);
        }
    }
    if (command.commands.front() == ":tab" || command.commands.front() == ":t")
    {
        command.consumed = true;
        Entity focusedView = Entity::find<Focus>()->focused;
        Prefabs::createTab("test", focusedView);
    }
    if (command.commands.front() == ":view" || command.commands.front() == ":v")
    {
        command.consumed = true;
        TabviewShared::show();
    }
}

