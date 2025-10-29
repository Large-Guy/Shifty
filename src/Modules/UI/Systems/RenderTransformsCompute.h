#ifndef SHIFTY_RENDERTRANSFORMSCOMPUTE_H
#define SHIFTY_RENDERTRANSFORMSCOMPUTE_H
#include "Drawing/Components/RenderTransform.h"
#include "ECS/Entity.h"
#include "ECS/System.h"
#include "UI/Components/Layout.h"
#include "UI/Components/Transform.h"


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
    static float computePositionProperty(Transform::Mode mode, float property, float start, float relativeTo);
    static void computeLayout(ComRef<Transform> transform, ComRef<RenderTransform> output, ComRef<Layout> layout,
                              int depth = 0);
    void process(OnLayout&) override;
};


#endif //SHIFTY_RENDERTRANSFORMSCOMPUTE_H
