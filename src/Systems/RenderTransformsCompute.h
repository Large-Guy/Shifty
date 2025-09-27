#ifndef SHIFTY_RENDERTRANSFORMSCOMPUTE_H
#define SHIFTY_RENDERTRANSFORMSCOMPUTE_H
#include "Components/Layout.h"
#include "Components/RenderTransform.h"
#include "Components/Transform.h"
#include "ECS/System.h"


struct OnLayout
{
    float relativeX;
    float relativeY;
    float relativeWidth;
    float relativeHeight;
};

class RenderTransformsCompute final : System<OnLayout>
{
    static float computeScaleProperty(Transform::Mode mode, float property, float relativeTo);
    static float computePositionProperty(Transform::Mode mode, float property, float relativeTo);
    static void computeLayout(const Transform& transform, RenderTransform& output, const Layout& layout);
    void process(const OnLayout&) override;
};


#endif //SHIFTY_RENDERTRANSFORMSCOMPUTE_H
