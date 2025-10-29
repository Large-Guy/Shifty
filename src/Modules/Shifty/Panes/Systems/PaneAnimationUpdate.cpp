#include "PaneAnimationUpdate.h"

#include <iostream>
#include <ostream>

#include "Drawing/Tween.h"
#include "UI/Components/Animation.h"
#include "UI/Components/Layout.h"
#include "UI/Components/Transform.h"
#include "ECS/Entity.h"
#include "Shifty/Panes/Components/Pane.h"

void PaneAnimationUpdate::process(OnUpdate&)
{
    Entity::multiEach<Animation, Layout, Pane, Transform>(
        [&](ComRef<Animation> animation, ComRef<Layout> layout, ComRef<Pane> view, ComRef<Transform> transform)
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
