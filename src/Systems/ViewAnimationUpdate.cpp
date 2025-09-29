#include "ViewAnimationUpdate.h"

#include <iostream>
#include <ostream>

#include "Tween.h"
#include "Components/Animation.h"
#include "Components/Layout.h"
#include "Components/Transform.h"
#include "Components/View.h"
#include "ECS/Entity.h"

void ViewAnimationUpdate::process(const OnUpdate&)
{
    Entity::multiEach<Animation, Layout, View, Transform>(
        [&](Animation& animation, Layout& layout, View& view, Transform& transform)
        {
            if (layout.parent != nullptr)
            {
                if (layout.parent.get<Layout>().type == Layout::Type::HORIZONTAL)
                {
                    transform.hMode = Transform::Mode::Auto;
                    transform.wMode = Transform::Mode::Percent;
                    transform.w = Tween::Lerp(0.0f, 1.0f, Tween::easeOutElastic(animation.time));
                }
                else if (layout.parent.get<Layout>().type == Layout::Type::VERTICAL)
                {
                    transform.wMode = Transform::Mode::Auto;
                    transform.hMode = Transform::Mode::Percent;
                    transform.h = Tween::Lerp(0.0f, 1.0f, Tween::easeOutElastic(animation.time));
                }
            }
        });
}
