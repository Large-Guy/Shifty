#include "TextDraw.h"

#include <iostream>

#include "TextRenderer.h"
#include "Components/RenderTransform.h"
#include "Components/Text.h"
#include "ECS/Entity.h"

TextCommand::TextCommand(float x, float y, float w, float h, const Text& text) : Command(100)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->text = text;
}

void TextCommand::execute(SDL_Renderer* renderer)
{
    SDL_FRect dest = {x, y, w, h};
    SDL_FRect src = {0, 0, w, h};

    SDL_RenderTexture(renderer, text.texture, &src, &dest);
}

void TextDraw::process(const OnDraw& onDraw)
{
    Entity::multiEach<Text, RenderTransform>([onDraw](Text& text, const RenderTransform& renderTransform)
    {
        float x = renderTransform.x;
        float y = renderTransform.y;

        float w, h;

        TextRenderer::sizeText(text.font->size(text.size), text.text, &w, &h);

        switch (text.horizontal)
        {
        case Text::Alignment::Leading:
            break;
        case Text::Alignment::Center:
            x = renderTransform.w / 2 - w / 2;
            break;
        case Text::Alignment::Trailing:
            x = renderTransform.w - w / 2;
            break;
        }

        switch (text.vertical)
        {
        case Text::Alignment::Leading:
            break;
        case Text::Alignment::Center:
            y = renderTransform.h / 2 - h / 2;
            break;
        case Text::Alignment::Trailing:
            y = renderTransform.h - h / 2;
            break;
        }

        h = std::min(renderTransform.h, h);

        if (text.rendered != text.text)
        {
            text.rendered = text.text;
            text.texture = TextRenderer::getTexture(onDraw.draw.renderer, text.font->size(text.size), text.text);
        }

        onDraw.draw.pushCommand(std::make_shared<TextCommand>(x, y, w, h, text));
    });
}
