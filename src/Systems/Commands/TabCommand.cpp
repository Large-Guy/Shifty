#include "TabCommand.h"

#include <iostream>

#include "Prefabs.h"
#include "Components/Focus.h"
#include "Components/RenderTransform.h"

static void split(Layout::Type type, Entity view)
{
    //We need to repeatedly use .get because creating entities can move components around
    if (view.get<Layout>()->parent != nullptr)
    {
        auto parentLayout = view.get<Layout>()->parent.get<Layout>();
        //Find my index
        auto myIndexIter = std::find(parentLayout->children.begin(), parentLayout->children.end(), view);
        size_t myIndex = std::distance(parentLayout->children.begin(), myIndexIter);
        Entity newView = Prefabs::createView();
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

void TabCommand::process(const OnCommandExecute& command)
{
    if (command.commands.empty())
        return;

    if (command.commands.front() == ":split" || command.commands.front() == ":sp")
    {
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
    if (command.commands.front() == ":t")
    {
        Entity focusedView = Entity::find<Focus>()->focused;
        Prefabs::createTab("test", focusedView);
    }
}

