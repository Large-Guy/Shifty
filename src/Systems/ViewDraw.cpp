#include "ViewDraw.h"

#include <iostream>
#include <random>

#include "Components/RenderTransform.h"
#include "Components/Transform.h"
#include "Components/View.h"
#include "ECS/Entity.h"

ViewDraw::Command::Command(ComRef<RenderTransform> renderTransform, ComRef<View> view) : Draw::Command(1),
    view(view),
    renderTransform(renderTransform)
{
}

void ViewDraw::Command::execute(SDL_Renderer* renderer)
{
    float x = renderTransform->overrideX ? renderTransform->overriddenX : renderTransform->x;
    float y = renderTransform->overrideY ? renderTransform->overriddenY : renderTransform->y;
    float w = renderTransform->overrideW ? renderTransform->overriddenW : renderTransform->w;
    float h = renderTransform->overrideH ? renderTransform->overriddenH : renderTransform->h;
    SDL_FRect rect = {x, y, w, h};
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    std::mt19937 gen((size_t)renderTransform.get());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    float r = dist(gen);
    float g = dist(gen);
    float b = dist(gen);

    float length = sqrt(r * r + g * g + b * b);

    r /= length;
    g /= length;
    b /= length;

    SDL_SetRenderDrawColorFloat(renderer, r, g, b, 0.5f);
    SDL_RenderFillRect(renderer, &rect);
}

ViewDraw::DebugRenderTransform::DebugRenderTransform(ComRef<RenderTransform> renderTransform) : Draw::Command(1),
    renderTransform(renderTransform)
{
}

void ViewDraw::DebugRenderTransform::execute(SDL_Renderer* renderer)
{
    float x = renderTransform->overrideX ? renderTransform->overrideX : renderTransform->x;
    float y = renderTransform->overrideY ? renderTransform->overrideY : renderTransform->y;
    float w = renderTransform->overrideW ? renderTransform->overrideW : renderTransform->w;
    float h = renderTransform->overrideH ? renderTransform->overrideH : renderTransform->h;
    SDL_FRect rect = {x, y, w, h};
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    std::mt19937 gen((size_t)renderTransform.get());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    float r = dist(gen);
    float g = dist(gen);
    float b = dist(gen);

    float length = sqrt(r * r + g * g + b * b);

    r /= length;
    g /= length;
    b /= length;

    SDL_SetRenderDrawColorFloat(renderer, r, g, b, 0.50f);
    SDL_RenderRect(renderer, &rect);
}


void ViewDraw::process(const OnDraw& draw)
{
    Entity::each<RenderTransform>([draw](ComRef<RenderTransform> transform)
    {
        //draw.draw->pushCommand(std::make_shared<DebugRenderTransform>(transform));
    });

    Entity::multiEach<RenderTransform, View>([draw](ComRef<RenderTransform> transform, ComRef<View> view)
    {
        draw.draw->pushCommand(std::make_shared<Command>(transform, view));
    });
}
