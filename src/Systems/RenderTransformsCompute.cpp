#include "RenderTransformsCompute.h"

#include <iostream>
#include <ostream>
#include <stdexcept>

#include "Components/Layout.h"
#include "Components/RenderTransform.h"
#include "Components/Transform.h"
#include "Components/Transform.h"
#include "ECS/Entity.h"

float RenderTransformsCompute::computeScaleProperty(Transform::Mode mode, float property, float relativeTo)
{
    if (mode == Transform::Mode::Pixel)
    {
        return property;
    }

    if (mode == Transform::Mode::Auto)
    {
        return relativeTo;
    }

    return property * relativeTo; //Percentage of parent
}

float RenderTransformsCompute::computePositionProperty(Transform::Mode mode, float property, float start,
                                                       float relativeTo)
{
    if (mode == Transform::Mode::Pixel)
    {
        return start + property;
    }

    if (mode == Transform::Mode::Auto)
    {
        return start + property * relativeTo; //Percentage of parent
    }

    return start + property * relativeTo; //Percentage of parent
}

void RenderTransformsCompute::computeLayout(const Transform& transform, RenderTransform& renderTransform,
                                            const Layout& layout)
{
    switch (layout.type)
    {
    case Layout::Type::FREE:
        {
            for (auto child : layout.children)
            {
                auto& render = child.get<RenderTransform>();
                auto& trans = child.get<Transform>();
                render.x = computePositionProperty(trans.xMode, trans.x, renderTransform.x, renderTransform.w);
                render.y = computePositionProperty(trans.yMode, trans.y, renderTransform.y, renderTransform.h);
                render.w = computeScaleProperty(trans.wMode, trans.w, renderTransform.w);
                render.h = computeScaleProperty(trans.hMode, trans.h, renderTransform.h);
            }
            break;
        }
    case Layout::Type::FULL:
        {
            if (layout.children.size() > 1)
                throw std::runtime_error("Full layout only permits one child!");
            if (!layout.children.empty())
            {
                auto& render = layout.children.front().get<RenderTransform>();
                render.x = renderTransform.x;
                render.y = renderTransform.y;
                render.w = renderTransform.w;
                render.h = renderTransform.h;
            }
            break;
        }
    case Layout::Type::VERTICAL:
        {
            //Calculate height override behavior
            float totalPercent = .0f;
            float remainingPixels = renderTransform.h;
            int autoCount = 0;
            for (auto child : layout.children)
            {
                auto& trans = child.get<Transform>();
                switch (trans.hMode)
                {
                case Transform::Mode::Pixel:
                    remainingPixels -= trans.h;
                    break;
                case Transform::Mode::Percent:
                    totalPercent += trans.h;
                    break;
                case Transform::Mode::Auto:
                    autoCount++;
                    break;
                }
            }

            float percentageScale = 1.f; //Force percentage boxes to fit

            if (totalPercent > 1.f)
            {
                percentageScale = 1.f / totalPercent;
            }

            remainingPixels -= computeScaleProperty(Transform::Mode::Percent, totalPercent, renderTransform.h);

            float consumed = .0f;

            float autoSize = remainingPixels / static_cast<float>(autoCount);
            for (int i = 0; i < layout.children.size(); i++)
            {
                auto& child = layout.children[i];
                auto& trans = child.get<Transform>();
                auto& render = child.get<RenderTransform>();

                //Constant x size
                render.x = computePositionProperty(trans.xMode, trans.x, renderTransform.x, renderTransform.w);
                render.w = computeScaleProperty(trans.wMode, trans.w, renderTransform.w);

                render.y = consumed;
                switch (trans.hMode)
                {
                case Transform::Mode::Pixel:
                    render.h = trans.h;
                    break;
                case Transform::Mode::Percent:
                    render.h = trans.h * renderTransform.h * percentageScale;
                    break;
                case Transform::Mode::Auto:
                    render.h = autoSize;
                    break;
                }
                consumed += render.h;
            }
            break;
        }
    case Layout::Type::HORIZONTAL:
        {
            //Calculate height override behavior
            float totalPercent = .0f;
            float remainingPixels = renderTransform.w;
            int autoCount = 0;
            for (auto child : layout.children)
            {
                auto& trans = child.get<Transform>();
                switch (trans.wMode)
                {
                case Transform::Mode::Pixel:
                    remainingPixels -= trans.w;
                    break;
                case Transform::Mode::Percent:
                    totalPercent += trans.w;
                    break;
                case Transform::Mode::Auto:
                    autoCount++;
                    break;
                }
            }

            float percentageScale = 1.f; //Force percentage boxes to fit

            if (totalPercent > 1.f)
            {
                percentageScale = 1.f / totalPercent;
            }

            remainingPixels -= computeScaleProperty(Transform::Mode::Percent, totalPercent, renderTransform.w);

            float consumed = .0f;

            float autoSize = remainingPixels / static_cast<float>(autoCount);
            for (int i = 0; i < layout.children.size(); i++)
            {
                auto& child = layout.children[i];
                auto& trans = child.get<Transform>();
                auto& render = child.get<RenderTransform>();

                //Constant y size
                render.y = computePositionProperty(trans.yMode, trans.x, renderTransform.y, renderTransform.h);
                render.h = computeScaleProperty(trans.hMode, trans.w, renderTransform.h);

                render.x = consumed;
                switch (trans.wMode)
                {
                case Transform::Mode::Pixel:
                    render.w = trans.w;
                    break;
                case Transform::Mode::Percent:
                    render.w = trans.w * renderTransform.w * percentageScale;
                    break;
                case Transform::Mode::Auto:
                    render.w = autoSize;
                    break;
                }
                consumed += render.w;
            }
            break;
        }
    }

    for (auto& child : layout.children)
    {
        computeLayout(child.get<Transform>(), child.get<RenderTransform>(), child.get<Layout>());
    }
}


void RenderTransformsCompute::process(const OnLayout& onLayout)
{
    Entity::multiEach<Transform, RenderTransform, Layout>(
        [&](Entity entity, const Transform& transform, RenderTransform& output, const Layout& layout)
        {
            output.x = computePositionProperty(transform.xMode, transform.x, onLayout.relativeX,
                                               onLayout.relativeWidth);
            output.y = computePositionProperty(transform.yMode, transform.y, onLayout.relativeY,
                                               onLayout.relativeHeight);
            output.w = computeScaleProperty(transform.wMode, transform.w, onLayout.relativeWidth);
            output.h = computeScaleProperty(transform.hMode, transform.h, onLayout.relativeHeight);


            computeLayout(transform, output, layout);
        }, [](Entity entity, Transform, RenderTransform&, const Layout& layout)
        {
            if (layout.parent.id == 0)
            {
                return true;
            }
            return false;
        });
}
