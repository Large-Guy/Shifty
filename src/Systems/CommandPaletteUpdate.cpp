#include "CommandPaletteUpdate.h"

#include "Tween.h"
#include "Components/Animation.h"
#include "Components/App.h"
#include "Components/CommandPalette.h"
#include "Components/Focus.h"
#include "Components/InputHandler.h"
#include "Components/Text.h"
#include "Components/Transform.h"
#include "ECS/Entity.h"

void CommandPaletteUpdate::process(const OnUpdate& onUpdate)
{
    Entity::multiEach<CommandPalette, Animation, Transform>(
        [onUpdate](Entity entity, ComRef<CommandPalette> palette, ComRef<Animation> animation,
                   ComRef<Transform> transform)
        {
            if (palette->open)
            {
                transform->h = Tween::Lerp(0.0f, 32.f, Tween::easeInOutCirc(animation->tracks["open"].time));
                Entity::findEntity<InputHandler>().get<InputHandler>()->textInput = true;
                if (Entity::find<Focus>()->focused != entity)
                {
                    palette->open = false;
                    Entity::find<App>()->state = App::State::Normal;
                }
            }
            else
            {
                transform->h = Tween::Lerp(32.f, 0.0f, Tween::easeInBack(animation->tracks["open"].time));
                Entity::findEntity<InputHandler>().get<InputHandler>()->textInput = false;
            }
        });
}
