#include "AnimationUpdate.h"

#include "GlobalConfig.h"
#include "Components/Animation.h"
#include "ECS/Entity.h"

void AnimationUpdate::process(const OnUpdate&)
{
    Entity::each<Animation>([&](Animation& anim)
    {
        anim.time += 0.016f * GlobalConfig::animationSpeed;
        if (anim.time >= 1.0f)
        {
            if (anim.loop)
                anim.time = 0.0f;
            else
                anim.time = 1.0f;
        }
    });
}
