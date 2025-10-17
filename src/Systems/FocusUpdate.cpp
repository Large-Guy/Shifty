#include "FocusUpdate.h"

#include "Components/Animation.h"
#include "Components/Focus.h"
#include "ECS/Entity.h"

void FocusUpdate::process(const OnUpdate& update)
{
    Entity::multiEach<Focus, Animation>([](ComRef<Focus> focus, ComRef<Animation> animation)
    {
        if (focus->focused != focus->focusChanged)
        {
            focus->previousFocused = focus->focusChanged;
            focus->focusChanged = focus->focused;
            animation->tracks["focus"].time = 0.0f;
        }
    });
}
