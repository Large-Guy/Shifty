#ifndef SHIFTY_DRAWSYSTEM_H
#define SHIFTY_DRAWSYSTEM_H
#include "Drawing/Components/Draw.h"
#include "ECS/Entity.h"

namespace DrawSystem
{
    struct alignas(16) UIRectInfo
    {
        float screenSize[2] = {1.0f, 1.0f};
        float start[2] = {0.0f, 0.0f};

        float rect[4] = {0.0f, 0.0f, 1.0f, 1.0f};
        float rounding[4] = {0.0f, 0.0f, 0.0f, 0.0f};

        float fillStart[4] = {0.0f, 0.0f, 0.0f, 0.0f};
        float fillEnd[4] = {0.0f, 0.0f, 0.0f, 0.0f};

        float outlineStart[4] = {1.0f, 1.0f, 1.0f, 1.0f};
        float outlineEnd[4] = {1.0f, 1.0f, 1.0f, 1.0f};

        float end[2] = {1.0f, 1.0f};
        float thickness = 1.0f;
        float pad0 = 0.0f;

        float motion[4] = {0.0f, 0.0f, 0.0f, 0.0f};

        float shadow = 0.0f;
        float startShadow = 0.0f;
        float endShadow = 0.0f;
    };

    void drawUIRect(ComRef<Draw> draw, const UIRectInfo& info);
};

#endif //SHIFTY_DRAWSYSTEM_H
