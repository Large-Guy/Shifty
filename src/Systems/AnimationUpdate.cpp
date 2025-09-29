#include "AnimationUpdate.h"

#include "GlobalConfig.h"
#include "Components/Animation.h"
#include "ECS/Entity.h"

void AnimationUpdate::process(const OnUpdate& update)
{
    Entity::each<Animation>([&](Animation& anim)
    {
        anim.time += update.deltaTime * GlobalConfig::animationSpeed * anim.speed;
        if (anim.time >= 1.0f)
        {
            if (anim.loop)
                anim.time = 0.0f;
            else
                anim.time = 1.0f;
        }
    });
}
