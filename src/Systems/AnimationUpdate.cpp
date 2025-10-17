#include "AnimationUpdate.h"

#include "GlobalConfig.h"
#include "Components/Animation.h"
#include "ECS/Entity.h"

void AnimationUpdate::process(const OnUpdate& update)
{
    Entity::each<Animation>([&](const ComRef<Animation>& anim)
    {
        for (auto& track : anim->tracks)
        {
            track.second.time += update.deltaTime * GlobalConfig::animationSpeed * track.second.speed;
            if (track.second.time >= 1.0f)
            {
                if (track.second.loop)
                    track.second.time = 0.0f;
                else
                    track.second.time = 1.0f;
            }
        }
    });
}

