#include "TabviewDraw.h"

#include "Components/Animation.h"
#include "Components/TabviewState.h"

TabviewDraw::Command::Command(ComRef<RenderTransform> renderTransform, float alpha) : Draw::Command(200)
{
    this->renderTransform = renderTransform;
    this->alpha = alpha;
}

void TabviewDraw::Command::execute(SDL_Renderer* renderer)
{
    float x = renderTransform->x;
    float y = renderTransform->y;
    float w = renderTransform->w;
    float h = renderTransform->h;
    SDL_FRect rect = {x, y, w, h};
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    SDL_SetRenderDrawColorFloat(renderer, 1.f, 1.f, 1.f, alpha);
    SDL_RenderRect(renderer, &rect);
}

void TabviewDraw::process(const OnDraw& draw)
{
    Entity state = Entity::findEntity<TabviewState>();

    float alpha = state.get<Animation>()->tracks["open"].time;
    if (!state.get<TabviewState>()->active)
        alpha = 1.f - state.get<Animation>()->tracks["open"].time;
    draw.draw->pushCommand(std::make_shared<Command>(state.get<RenderTransform>(), alpha));
}
