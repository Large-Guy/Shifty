#include "PanelDraw.h"

#include <random>

#include "Components/Panel.h"
#include "Components/RenderTransform.h"


PanelDraw::Command::Command(ComRef<RenderTransform> renderTransform) : Draw::Command(50),
                                                                       renderTransform(renderTransform)
{
}

void PanelDraw::Command::execute(SDL_Renderer* renderer)
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


void PanelDraw::process(const OnDraw& draw)
{
    Entity::multiEach<Panel, RenderTransform>([draw](ComRef<Panel> view, ComRef<RenderTransform> transform)
    {
        draw.draw->pushCommand(std::make_shared<Command>(transform));
    });
}

