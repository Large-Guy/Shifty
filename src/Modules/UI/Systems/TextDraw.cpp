#include "TextDraw.h"

#include <iostream>

#include "Drawing/Components/RenderTransform.h"
#include "ECS/Entity.h"
#include "Text/TextRenderer.h"
#include "UI/Components/Text.h"

TextDraw::Command::Command(SDL_FRect render, ComRef<Text> text) : Draw::Command(250), render(render), text(text)
{
}

void TextDraw::Command::execute(SDL_Renderer* renderer)
{
    float scale;
    SDL_GetRenderScale(renderer, &scale, &scale);

    SDL_FRect dest = {render.x, render.y, render.w / scale, render.h / scale};
    SDL_FRect src = {0, 0, render.w, render.h};

    //SDL_SetTextureColorMod(text->texture, 0, 0, 0);

    //SDL_RenderTexture(renderer, text->texture, &src, &dest);
}

void TextDraw::process(OnDraw& onDraw)
{
    Entity::multiEach<Text, RenderTransform>([onDraw](ComRef<Text> text, ComRef<RenderTransform> renderTransform)
    {
        float scale;
        SDL_GetRenderScale(onDraw.draw->renderer, &scale, &scale);

        float x = renderTransform->x;
        float y = renderTransform->y;

        float w, h;

        TextRenderer::sizeText(text->font->size(text->size), text->text, &w, &h);

        switch (text->horizontal)
        {
        case Text::Alignment::Leading:
            break;
        case Text::Alignment::Center:
            x += renderTransform->w / 2 - w / 2;
            break;
        case Text::Alignment::Trailing:
            x += renderTransform->w - w / 2;
            break;
        }

        switch (text->vertical)
        {
        case Text::Alignment::Leading:
            break;
        case Text::Alignment::Center:
            y += renderTransform->h / 2 - h / 2;
            break;
        case Text::Alignment::Trailing:
            y += renderTransform->h - h / 2;
            break;
        }

        h = std::min(renderTransform->h, h);

        if (text->rendered != text->text)
        {
            text->rendered = text->text;
            text->texture =
                TextRenderer::getTexture(onDraw.draw->device, text->font->size(text->size * scale), text->text);
        }

        onDraw.draw->pushCommand(std::make_shared<Command>(SDL_FRect{x, y, w * scale, h * scale}, text));
    });
}
