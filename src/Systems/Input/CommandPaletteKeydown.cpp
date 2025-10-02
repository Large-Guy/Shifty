#include <chrono>

#include "CommandPaletteKeydown.h"

#include <iostream>

#include "Components/Animation.h"
#include "Components/CommandPalette.h"
#include "Components/Edit.h"
#include "Components/Focus.h"
#include "Components/Root.h"
#include "Components/Text.h"
#include "Components/Transform.h"
#include "Components/Panel.h"
#include "ECS/Entity.h"
#include "Systems/TextEditSystems.h"
#include "Systems/Shared/EditShared.h"

std::vector<std::string> split(const std::string& txt, char ch)
{
    std::vector<std::string> strs;
    size_t pos = txt.find(ch);
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while (pos != std::string::npos)
    {
        strs.push_back(txt.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;

        pos = txt.find(ch, initialPos);
    }

    // Add the last one
    strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

    return strs;
}

void CommandPaletteKeydown::process(const OnKeyPress& keyPress)
{
    using namespace std::chrono;
    uint64_t time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    if (keyPress.key == SDLK_LSHIFT || keyPress.key == SDLK_RSHIFT)
    {
        Entity::multiEach<Layout, CommandPalette, Animation, Text, Edit>(
            [time](Entity entity, ComRef<Layout> layout, ComRef<CommandPalette> commandPalette,
                   ComRef<Animation> animation, ComRef<Text> text,
                   ComRef<Edit> edit)
            {
                if (commandPalette->open)
                    return;

                uint64_t elapsed = time - commandPalette->lastShiftPressed;
                if (elapsed < 200)
                {
                    commandPalette->open = true;
                    animation->time = 0;
                    edit->highlightStart = 0;
                    edit->cursor = text->text.length();
                    EditShared::deleteSelection(text, edit);
                    Entity::find<Focus>()->focused = entity;
                }
                commandPalette->lastShiftPressed = time;
            }, [](Entity entity, ComRef<Layout> layout, ComRef<CommandPalette> _palette, ComRef<Animation> _animation,
                  ComRef<Text> _text,
                  ComRef<Edit> _edit)
            {
                if (layout->parent != nullptr)
                {
                    return Entity::find<Focus>()->focused == layout->parent;
                }

                return false;
            });
    }
    else if (keyPress.key == SDLK_ESCAPE)
    {
        Entity::multiEach<Layout, CommandPalette, Animation>(
            [](ComRef<Layout> layout, ComRef<CommandPalette> commandPalette, ComRef<Animation> animation)
            {
                if (!commandPalette->open)
                    return;

                commandPalette->open = false;
                animation->time = 0;
                Entity::find<Focus>()->focused = layout->parent;
            });
    }
    else if (keyPress.key == SDLK_RETURN)
    {
        Entity::multiEach<Layout, CommandPalette, Animation, Text>(
            [](ComRef<Layout> layout, ComRef<CommandPalette> commandPalette, ComRef<Animation> animation,
               ComRef<Text> text)
            {
                if (!commandPalette->open)
                    return;

                Entity::find<Focus>()->focused = layout->parent;

                EventBus::emit(OnCommandExecute{
                    .view = layout->parent,
                    .commands = split(text->text, ' ')
                });

                commandPalette->open = false;
                animation->time = 0;
            });
    }
    else
    {
        Entity::each<CommandPalette>([](ComRef<CommandPalette> commandPalette)
        {
            commandPalette->lastShiftPressed = 0;
        });
    }
}
