#include "SplitCommand.h"

#include <iostream>

#include "Prefabs.h"
#include "Components/RenderTransform.h"

static void split(Layout::Type type, Entity view)
{
    //We need to repeatedly use .get because creating entities can move components around
    if (view.get<Layout>().parent != nullptr)
    {
        auto& parentLayout = view.get<Layout>().parent.get<Layout>();
        Entity newView = Prefabs::createView();
        if (parentLayout.type == type)
        {
            Layout::addChild(view.get<Layout>().parent, newView);
        }
        else
        {
            Entity newLayout = Prefabs::createLayout(type);
            Layout::addChild(view.get<Layout>().parent, newLayout);
            Layout::addChild(newLayout, view);
            Layout::addChild(newLayout, newView);
        }
    }
    else
    {
        throw std::runtime_error("No parent layout");
    }
}

void SplitCommand::process(const OnCommandExecute& command)
{
    if (command.commands.empty())
        return;

    if (command.commands.front() == "/split" || command.commands.front() == "/sp")
    {
        //Splits the panel the long way
        RenderTransform transform = command.view.get<RenderTransform>();

        //Determine the long way
        if (transform.w > transform.h)
        {
            split(Layout::Type::HORIZONTAL, command.view);
        }
        else
        {
            split(Layout::Type::VERTICAL, command.view);
        }
    }
}

