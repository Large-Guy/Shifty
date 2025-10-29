#include "CommandPaletteUpdate.h"

#include "Drawing/Tween.h"
#include "UI/Components/Animation.h"
#include "Platform/EventHandler.h"
#include "UI/Components/Transform.h"
#include "ECS/Entity.h"
#include "Shifty/App/Components/App.h"
#include "Shifty/CommandPalette/Components/CommandPalette.h"
#include "UI/Components/Focus.h"

void CommandPaletteUpdate::process(OnUpdate& onUpdate)
{
    Entity::multiEach<CommandPalette, Animation, Transform>(
        [onUpdate](Entity entity, ComRef<CommandPalette> palette, ComRef<Animation> animation,
                   ComRef<Transform> transform)
        {
            if (palette->open)
            {
                transform->h = Tween::Lerp(0.0f, 32.f, Tween::easeInOutCirc(animation->tracks["open"].time));
                Entity::find<App>()->handler->textInput = true;
                if (Entity::find<Focus>()->focused != entity)
                {
                    palette->open = false;
                    Entity::find<App>()->state = App::State::Normal;
                }
            }
            else
            {
                transform->h = Tween::Lerp(32.f, 0.0f, Tween::easeInBack(animation->tracks["open"].time));
                Entity::find<App>()->handler->textInput = false;
            }
        });
}
