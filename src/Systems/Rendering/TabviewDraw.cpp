#include "TabviewDraw.h"

#include "Drawing.h"
#include "Components/Animation.h"
#include "Components/TabviewState.h"

TabviewDraw::Command::Command(ComRef<RenderTransform> renderTransform, float alpha) : Draw::Command(200)
{
    this->renderTransform = renderTransform;
    this->alpha = alpha;
}

void TabviewDraw::Command::execute(SDL_Renderer* renderer)
{
    float x = renderTransform->x - 4.0f;
    float y = renderTransform->y - 4.0f;
    float w = renderTransform->w + 8.0f;
    float h = renderTransform->h + 8.0f;
    SDL_FRect rect = {x, y, w, h};
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    SDL_SetRenderDrawColorFloat(renderer, 1.f, 1.f, 1.f, alpha);
    SDL_RenderRect(renderer, &rect);
    ComRef<Draw> draw = Entity::find<Draw>();
    Drawing::drawUIRect(draw, {
                            .screenSize = {static_cast<float>(draw->width), static_cast<float>(draw->height)},
                            .start = {0.0f, 0.0f},
                            .rect = {rect.x, rect.y, rect.w, rect.h},
                            .rounding = {16.0f, 16.0f, 16.0f, 16.0f},

                            .fillStart = {1.0f, 1.0f, 1.0f, 0.0f},
                            .fillEnd = {1.0f, 1.0f, 1.0f, 0.0f},
                            .outlineStart = {1.0f, 1.0f, 1.0f, alpha},
                            .outlineEnd = {1.0f, 1.0f, 1.0f, alpha},
                            .end = {0.5f, 1.0f},

                            .thickness = 2.0f,
                        });
}

void TabviewDraw::process(const OnDraw& draw)
{
    Entity state = Entity::findEntity<TabviewState>();

    float alpha = state.get<Animation>()->tracks["open"].time;
    if (!state.get<TabviewState>()->active)
        alpha = 1.f - state.get<Animation>()->tracks["open"].time;
    draw.draw->pushCommand(std::make_shared<Command>(state.get<RenderTransform>(), alpha));
}
