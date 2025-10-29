#include "PaneDraw.h"

#include <random>

#include "Drawing/Systems/DrawSystem.h"
#include "Drawing/Tween.h"
#include "UI/Components/Animation.h"
#include "UI/Components/Focus.h"
#include "Drawing/Components/RenderTransform.h"
#include "Shifty/Panes/Components/Pane.h"


PaneDraw::Command::Command(ComRef<RenderTransform> renderTransform) : Draw::Command(0),
                                                                      renderTransform(renderTransform)
{
}

void PaneDraw::Command::execute(SDL_Renderer* renderer)
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

    float tween = 0.0f;
    float thicknessTween = 0.0f;

    if (Entity::find<Focus>()->focused == renderTransform.owner)
    {
        float time = Entity(renderTransform.owner).get<Animation>()->tracks["focusStart"].time;
        tween = Tween::easeOutQuint(time);
        thicknessTween = Tween::easeInOutQuart(time);
    }
    else
    {
        float time = Entity(renderTransform.owner).get<Animation>()->tracks["focusEnd"].time;
        tween = 1.0f - Tween::easeOutQuint(time);
        thicknessTween = 1.0f - Tween::easeInOutQuart(time);
    }

    ComRef<Draw> draw = Entity::find<Draw>();
    DrawSystem::drawUIRect(draw, {
                               .screenSize = {static_cast<float>(draw->width), static_cast<float>(draw->height)},
                               .start = {0.0f, 0.0f},
                               .rect = {rect.x, rect.y, rect.w, rect.h},
                               .rounding = {32.0f, 32.0f, 32.0f, 32.0f},

                               .fillStart = {1.0f, 1.0f, 1.0f, 0.3f * tween},
                               .fillEnd = {1.0f, 1.0f, 1.0f, 0.33f * tween},

                               .outlineStart = {0.1f, 0.5f, 1.0f, 0.7f},
                               .outlineEnd = {0.1f, 0.5f, 1.0f, 0.8f},

                               .end = {0.5f, 1.0f},

                               .thickness = 8.0f * thicknessTween,
                           });
}


void PaneDraw::process(OnDraw& draw)
{
    Entity::multiEach<Pane, RenderTransform>([&draw](ComRef<Pane>, ComRef<RenderTransform> transform)
    {
        draw.draw->pushCommand(std::make_shared<Command>(transform));
    });
}

