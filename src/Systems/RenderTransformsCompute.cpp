#include "RenderTransformsCompute.h"

#include "Components/Layout.h"
#include "Components/Parent.h"
#include "Components/RenderTransform.h"
#include "Components/Transform.h"
#include "Components/Transform.h"
#include "ECS/Entity.h"

float computeProperty(Transform::Mode mode, float property, float relativeTo) {
    if (mode == Transform::Mode::Pixel) {
        return property;
    }

    return property * relativeTo; //Percentage of parent
}

void RenderTransformsCompute::process(const OnLayout& onLayout) {
    Entity::multiEach<Transform, RenderTransform, Layout>(
        [&](Entity entity, const Transform& transform, RenderTransform& output, Layout& layout) {
            float relativeWidth = onLayout.relativeWidth;
            float relativeHeight = onLayout.relativeHeight;
            if (entity.has<Parent>() && entity.get<Parent>().entity.has<Transform>()) {
            }
            output.x = computeProperty(transform.xMode, transform.x, onLayout.relativeWidth);
            output.y = computeProperty(transform.yMode, transform.y, onLayout.relativeHeight);
            output.w = computeProperty(transform.wMode, transform.w, onLayout.relativeWidth);
            output.h = computeProperty(transform.hMode, transform.h, onLayout.relativeHeight);
        }, [](Entity entity, Transform, RenderTransform& output, Layout& layout) {
            if (layout.parent.id == 0) {
                return true;
            }
            return false;
        });
}
