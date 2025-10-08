#include "PanelDraw.h"

#include <random>

#include "Tween.h"
#include "Components/Animation.h"
#include "Components/Focus.h"
#include "Components/Panel.h"
#include "Components/RenderTransform.h"


PanelDraw::Command::Command(ComRef<RenderTransform> renderTransform) : Draw::Command(0),
                                                                       renderTransform(renderTransform)
{
}

void PanelDraw::Command::execute(SDL_Renderer* renderer)
{
    float x = renderTransform->x;
    float y = renderTransform->y;
    float w = renderTransform->w + 0.5f;
    float h = renderTransform->h + 0.5f;
    SDL_FRect rect = {x, y, w, h};
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;

    if (Entity::find<Focus>()->focused == renderTransform.owner)
    {
        SDL_SetRenderDrawColorFloat(renderer, r, g, b,
                                    Tween::easeOutQuint(Entity::findEntity<Focus>().get<Animation>()->time) * 0.4f);
        SDL_RenderFillRect(renderer, &rect);

        SDL_SetRenderDrawColorFloat(renderer, 1.0f, 1.0f, 1.0f, 0.67f);
        SDL_RenderRect(renderer, &rect);
    }
    else
    {
        SDL_SetRenderDrawColorFloat(renderer, 1.0f, 1.0f, 1.0f, 0.2f);
        SDL_RenderRect(renderer, &rect);
    }
}


void PanelDraw::process(const OnDraw& draw)
{
    Entity::multiEach<Panel, RenderTransform>([&draw](ComRef<Panel>, ComRef<RenderTransform> transform)
    {
        draw.draw->pushCommand(std::make_shared<Command>(transform));
    });
}

