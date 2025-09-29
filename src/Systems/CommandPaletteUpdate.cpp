#include "CommandPaletteUpdate.h"

#include "Tween.h"
#include "Components/Animation.h"
#include "Components/App.h"
#include "Components/CommandPalette.h"
#include "Components/InputHandler.h"
#include "Components/Text.h"
#include "Components/Transform.h"
#include "ECS/Entity.h"

void CommandPaletteUpdate::process(const OnUpdate& onUpdate)
{
    Entity::multiEach<CommandPalette, Animation, Transform>(
        [onUpdate](const CommandPalette& palette, Animation& animation, Transform& transform)
        {
            if (palette.open)
            {
                transform.h = Tween::Lerp(0.0f, 32.f, Tween::easeInOutCirc(animation.time));
                Entity::findEntity<InputHandler>().get<InputHandler>().textInput = true;
            }
            else
            {
                transform.h = Tween::Lerp(32.f, 0.0f, Tween::easeInBack(animation.time));
                Entity::findEntity<InputHandler>().get<InputHandler>().textInput = false;
            }
        });
}
