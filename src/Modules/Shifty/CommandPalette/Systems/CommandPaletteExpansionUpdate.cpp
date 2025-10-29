#include "CommandPaletteExpansionUpdate.h"

#include <cmath>
#include <iostream>

#include "Config/GlobalConfig.h"
#include "../../../Text/TextRenderer.h"
#include "Drawing/Tween.h"
#include "Drawing/Components/RenderTransform.h"
#include "UI/Components/Text.h"
#include "UI/Components/Transform.h"
#include "ECS/Entity.h"
#include "Shifty/CommandPalette/Components/CommandPalette.h"

void CommandPaletteExpansionUpdate::process(OnUpdate& update)
{
    Entity::multiEach<CommandPalette, Transform, RenderTransform, Text, Layout>(
        [&](ComRef<CommandPalette> palette, ComRef<Transform> transform, ComRef<RenderTransform> render,
            ComRef<Text> text, ComRef<Layout> layout)
        {
            if (layout->parent == Entity::null)
                return;

            float maxWidth = layout->parent.get<RenderTransform>()->w;

            float width, height;
            TextRenderer::sizeText(text->font->size(text->size), text->text, &width, &height);

            width += 10;

            if (width > maxWidth)
            {
                const float rate = update.deltaTime * 10.f;
                const float x = -std::log(rate / (width - maxWidth)) / GlobalConfig::Appearance::animationSpeed;

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
