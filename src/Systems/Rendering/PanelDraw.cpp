#include "PanelDraw.h"

#include <random>

#include "Drawing.h"
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
        float tween = Tween::easeOutQuint(Entity(renderTransform.owner).get<Animation>()->tracks["focus"].time);

        float thicknessTween =
            Tween::easeInOutQuart(Entity(renderTransform.owner).get<Animation>()->tracks["focus"].time);

        ComRef<Draw> draw = Entity::find<Draw>();
        Drawing::drawUIRect(draw, {
                                .screenSize = {static_cast<float>(draw->width), static_cast<float>(draw->height)},
                                .start = {0.0f, 0.0f},
                                .rect = {rect.x, rect.y, rect.w, rect.h},
                                .rounding = {8.0f, 8.0f, 8.0f, 8.0f},

                                .fillStart = {1.0f, 1.0f, 1.0f, 0.5f * tween},
                                .fillEnd = {1.0f, 1.0f, 1.0f, 0.67f * tween},
                                .end = {0.5f, 1.0f},

                                .thickness = 8.0f * thicknessTween,
                            });
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

