#include <chrono>

#include "CommandPaletteKeydown.h"

#include "Components/Animation.h"
#include "Components/CommandPalette.h"
#include "ECS/Entity.h"

void CommandPaletteKeydown::process(const OnKeyPress& keyPress)
{
    using namespace std::chrono;
    uint64_t time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    if (keyPress.key == SDLK_LSHIFT || keyPress.key == SDLK_RSHIFT)
    {
        Entity::multiEach<CommandPalette, Animation>([time](CommandPalette& commandPalette, Animation& animation)
        {
            if (commandPalette.open)
                return;

            uint64_t elapsed = time - commandPalette.lastShiftPressed;
            if (elapsed < 200)
            {
                commandPalette.open = true;
                animation.time = 0;
            }
            commandPalette.lastShiftPressed = time;
        });
    }
    else if (keyPress.key == SDLK_ESCAPE || keyPress.key == SDLK_RETURN)
    {
        Entity::multiEach<CommandPalette, Animation>([](CommandPalette& commandPalette, Animation& animation)
        {
            if (!commandPalette.open)
                return;

            commandPalette.open = false;
            animation.time = 0;
        });
    }
    else
    {
        Entity::each<CommandPalette>([](CommandPalette& commandPalette)
        {
            commandPalette.lastShiftPressed = 0;
        });
    }
}
