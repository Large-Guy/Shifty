#ifndef SHIFTY_DRAWING_H
#define SHIFTY_DRAWING_H
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>

#include "Components/Draw.h"

//Helper class to handle drawing UI components and stuff
//This is to help cover up vulkan functionality
class Drawing
{
public:
    struct alignas(16) UIRectInfo
    {
        float screenSize[2];
        float start[2];

        float rect[4];
        float rounding[4];

        float fillStart[4];
        float fillEnd[4];

        float end[2];
        float thickness;
        float pad0;

        float motion[4];

        float shadow;
        float startShadow;
        float endShadow;
    };

    static void drawUIRect(ComRef<Draw> draw, const UIRectInfo& info);
};


#endif //SHIFTY_DRAWING_H
