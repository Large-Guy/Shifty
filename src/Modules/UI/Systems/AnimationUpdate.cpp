#include "AnimationUpdate.h"

#include "Config/GlobalConfig.h"
#include "ECS/Entity.h"
#include "UI/Components/Animation.h"

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

