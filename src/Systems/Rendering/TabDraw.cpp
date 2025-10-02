#include "TabDraw.h"

#include <iostream>
#include <random>

#include "Components/RenderTransform.h"
#include "Components/Transform.h"
#include "Components/Panel.h"
#include "ECS/Entity.h"

TabDraw::Command::Command(ComRef<RenderTransform> renderTransform, ComRef<Tab> tab, int layer) :
    Draw::Command(30 - layer),
    tab(tab),
    renderTransform(renderTransform)
{
}

void TabDraw::Command::execute(SDL_Renderer* renderer)
{
    float x = renderTransform->x;
    float y = renderTransform->y;
    float w = renderTransform->w;
    float h = renderTransform->h;
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

    SDL_SetRenderDrawColorFloat(renderer, r, g, b, 1.0f);
    SDL_RenderFillRect(renderer, &rect);
}

TabDraw::DebugRenderTransform::DebugRenderTransform(ComRef<RenderTransform> renderTransform) : Draw::Command(50),
    renderTransform(renderTransform)
{
}

void TabDraw::DebugRenderTransform::execute(SDL_Renderer* renderer)
{
    float x = renderTransform->x;
    float y = renderTransform->y;
    float w = renderTransform->w;
    float h = renderTransform->h;
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


void TabDraw::process(const OnDraw& draw)
{
    Entity::multiEach<Panel, RenderTransform>([draw](ComRef<Panel> view, ComRef<RenderTransform> transform)
    {
        draw.draw->pushCommand(std::make_shared<DebugRenderTransform>(transform));
    });

    Entity::multiEach<RenderTransform, Panel>([draw](ComRef<RenderTransform> transform, ComRef<Panel> view)
    {
        if (view->holdingTabs.empty())
            return;

        for (int i = 0; i < view->holdingTabs.size(); ++i)
        {
            draw.draw->pushCommand(
                std::make_shared<Command>(view->holdingTabs[i].get<RenderTransform>(),
                                          view->holdingTabs[i].get<Tab>(), i));
        }
    });
}
