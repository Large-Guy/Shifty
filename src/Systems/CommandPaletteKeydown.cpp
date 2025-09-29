#include <chrono>

#include "CommandPaletteKeydown.h"

#include <iostream>

#include "TextEditSystems.h"
#include "Components/Animation.h"
#include "Components/CommandPalette.h"
#include "Components/Edit.h"
#include "Components/Focus.h"
#include "Components/Root.h"
#include "Components/Text.h"
#include "Components/Transform.h"
#include "Components/View.h"
#include "ECS/Entity.h"

void CommandPaletteKeydown::process(const OnKeyPress& keyPress)
{
    using namespace std::chrono;
    uint64_t time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    if (keyPress.key == SDLK_LSHIFT || keyPress.key == SDLK_RSHIFT)
    {
        Entity::multiEach<Layout, CommandPalette, Animation, Text, Edit>(
            [time](Entity entity, Layout& layout, CommandPalette& commandPalette, Animation& animation, Text& text,
                   Edit& edit)
            {
                if (commandPalette.open)
                    return;

                uint64_t elapsed = time - commandPalette.lastShiftPressed;
                if (elapsed < 200)
                {
                    commandPalette.open = true;
                    animation.time = 0;
                    edit.highlightStart = 0;
                    edit.cursor = text.text.length();
                    EditShared::deleteSelection(text, edit);
                    Entity::find<Focus>().focused = entity;
                }
                commandPalette.lastShiftPressed = time;
            }, [](Entity& entity, const Layout& layout, CommandPalette& _palette, Animation& _animation, Text& _text,
                  Edit& _edit)
            {
                if (layout.parent != nullptr)
                {
                    return Entity::find<Focus>().focused == layout.parent;
                }

                return false;
            });
    }
    else if (keyPress.key == SDLK_ESCAPE || keyPress.key == SDLK_RETURN)
    {
        Entity::multiEach<Layout, CommandPalette, Animation>(
            [](Layout& layout, CommandPalette& commandPalette, Animation& animation)
            {
                if (!commandPalette.open)
                    return;

                commandPalette.open = false;
                animation.time = 0;
                Entity::find<Focus>().focused = layout.parent;
            });
    }
    else
    {
        Entity::each<CommandPalette>([](CommandPalette& commandPalette)
        {
            commandPalette.lastShiftPressed = 0;
        });
    }

    //TODO: Have these split properly before I push this commit

    //Debugging things
    if (keyPress.key == SDLK_F1) //Horizontal split
    {
        Entity root = Entity::findEntity<Root>();
        root.get<Layout>().type = Layout::Type::HORIZONTAL;
        Entity padding = Entity::create();
        padding.add<View>();
        padding.add<Animation>();
        padding.add<Transform>();
        padding.add<RenderTransform>();
        padding.add<Layout>();

        Layout::addChild(root, padding);
    }

    if (keyPress.key == SDLK_F2) //Horizontal split
    {
        Entity root = Entity::findEntity<Root>();
        root.get<Layout>().type = Layout::Type::VERTICAL;
        Entity padding = Entity::create();
        padding.add<View>();
        padding.add<Animation>();
        padding.add<Transform>();
        padding.add<RenderTransform>();
        padding.add<Layout>();

        Layout::addChild(root, padding);
    }
}
