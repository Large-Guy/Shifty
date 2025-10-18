#include "FocusUpdate.h"

#include "ECS/Entity.h"
#include "UI/Components/Animation.h"
#include "UI/Components/Focus.h"

void FocusUpdate::process(const OnUpdate& update)
{
    Entity::multiEach<Focus, Animation>([](ComRef<Focus> focus, ComRef<Animation> animation)
    {
        if (focus->focused != focus->focusChanged)
        {
            focus->previousFocused = focus->focusChanged;
            if (focus->previousFocused != Entity::null && focus->previousFocused.has<Animation>())
            {
                focus->previousFocused.get<Animation>()->tracks["focusEnd"].time = 0.0f;
            }
            focus->focusChanged = focus->focused;

            if (focus->focused.has<Animation>())
            {
                focus->focused.get<Animation>()->tracks["focusStart"].time = 0.0f;
            }
        }
    });
}
