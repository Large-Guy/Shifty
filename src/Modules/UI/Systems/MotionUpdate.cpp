#include "MotionUpdate.h"

#include "Drawing/Components/RenderTransform.h"
#include "ECS/Entity.h"
#include "UI/Components/Motion.h"

void MotionUpdate::process(const OnUpdate&)
{
    Entity::multiEach<RenderTransform, Motion>(
        [](const ComRef<RenderTransform>& transform, const ComRef<Motion>& motion)
        {
            float x = (transform->x * 2.0f + transform->w) / 2.0f;
            float y = (transform->y * 2.0f + transform->h) / 2.0f;
            motion->deltaX = x - motion->prevX;
            motion->deltaY = y - motion->prevY;
            motion->deltaW = transform->w - motion->prevW;
            motion->deltaH = transform->h - motion->prevH;
            motion->prevX = x;
            motion->prevY = y;
            motion->prevW = transform->w;
            motion->prevH = transform->h;
        });
}
