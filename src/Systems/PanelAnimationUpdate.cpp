#include "PanelAnimationUpdate.h"

#include <iostream>
#include <ostream>

#include "Tween.h"
#include "Components/Animation.h"
#include "Components/Layout.h"
#include "Components/Transform.h"
#include "Components/Panel.h"
#include "ECS/Entity.h"

void PanelAnimationUpdate::process(const OnUpdate&)
{
    Entity::multiEach<Animation, Layout, Panel, Transform>(
        [&](ComRef<Animation> animation, ComRef<Layout> layout, ComRef<Panel> view, ComRef<Transform> transform)
        {
            if (animation->tracks["open"].time > 1.0f)
                return;
            if (layout->parent != Entity::null)
            {
                if (layout->parent.get<Layout>()->type == Layout::Type::HORIZONTAL)
                {
                    transform->hMode = Transform::Mode::Auto;
                    transform->wMode = Transform::Mode::Percent;
                    transform->w = Tween::Lerp(0.0f, 1.0f, Tween::easeOutElastic(animation->tracks["open"].time));
                }
                else if (layout->parent.get<Layout>()->type == Layout::Type::VERTICAL)
                {
                    transform->wMode = Transform::Mode::Auto;
                    transform->hMode = Transform::Mode::Percent;
                    transform->h = Tween::Lerp(0.0f, 1.0f, Tween::easeOutElastic(animation->tracks["open"].time));
                }
            }
        });
}
