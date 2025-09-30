#include "CommandPaletteExpansionUpdate.h"

#include <iostream>

#include "GlobalConfig.h"
#include "Tween.h"
#include "Components/CommandPalette.h"
#include "Components/RenderTransform.h"
#include "Components/Text.h"
#include "Components/Transform.h"
#include "ECS/Entity.h"

void CommandPaletteExpansionUpdate::process(const OnUpdate& update)
{
    Entity::multiEach<CommandPalette, Transform, RenderTransform, Text, Layout>(
        [&](ComRef<CommandPalette> palette, ComRef<Transform> transform, ComRef<RenderTransform> render,
            ComRef<Text> text, ComRef<Layout> layout)
        {
            if (layout->parent == nullptr)
                return;

            float maxWidth = layout->parent.get<RenderTransform>()->w;

            float width, height;
            TextRenderer::sizeText(text->font->size(text->size), text->text, &width, &height);

            width += 10;

            if (width > maxWidth)
            {
                const float rate = update.deltaTime * 10.f;
                const float x = -std::log(rate / (width - maxWidth)) / GlobalConfig::animationSpeed;

                transform->wMode = Transform::Mode::Pixel;
                transform->w = Tween::Lerp(transform->w, width, rate * x);
            }
            else
            {
                if (transform->w < maxWidth)
                {
                    transform->w = maxWidth;
                }
                transform->wMode = Transform::Mode::Pixel;
                transform->w = Tween::Lerp(transform->w, maxWidth, update.deltaTime * 5.f);
            }
        });
}
