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
    float w = renderTransform->w;
    float h = renderTransform->h;
    SDL_FRect rect = {x, y, w, h};
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;

    SDL_SetRenderDrawColorFloat(renderer, r, g, b,
                                Tween::easeOutQuint(Entity::findEntity<Focus>().get<Animation>()->time) * 0.5f);
    SDL_RenderFillRect(renderer, &rect);
}


void PanelDraw::process(const OnDraw& draw)
{
    if (Entity::find<Focus>()->focused.has<Panel>())
    {
        draw.draw->pushCommand(std::make_shared<Command>(Entity::find<Focus>()->focused.get<RenderTransform>()));
    }
}

