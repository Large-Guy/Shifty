#ifndef SHIFTY_RENDERTRANSFORMSCOMPUTE_H
#define SHIFTY_RENDERTRANSFORMSCOMPUTE_H
#include "ECS/System.h"


struct OnLayout {
    float relativeWidth;
    float relativeHeight;
};

class RenderTransformsCompute final : System<OnLayout> {
    void process(const OnLayout&) override;
};


#endif //SHIFTY_RENDERTRANSFORMSCOMPUTE_H