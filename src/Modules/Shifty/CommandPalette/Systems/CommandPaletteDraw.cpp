#include "CommandPaletteDraw.h"

#include "Drawing/DrawSystem.h"
#include "Shifty/CommandPalette/Components/CommandPalette.h"

CommandPaletteDraw::Command::Command(ComRef<RenderTransform> transform) : Draw::Command(150)
{
    this->transform = transform;
}

void CommandPaletteDraw::Command::execute(SDL_Renderer* renderer)
{
    SDL_FRect rect = {transform->x, transform->y, transform->w, transform->h};

    ComRef<Draw> draw = Entity::find<Draw>();
    DrawSystem::drawUIRect(draw, {
                               .screenSize = {static_cast<float>(draw->width), static_cast<float>(draw->height)},
                               .start = {0.0f, 0.0f},
                               .rect = {rect.x, rect.y, rect.w, rect.h},
                               .rounding = {16.0f, 0.0f, 16.0f, 0.0f},

                               .fillStart = {0.93f, 0.93f, 0.93f, 0.8f},
                               .fillEnd = {0.93f, 0.93f, 0.93f, 1.0f},
                               .end = {0.0f, 1.0f},

                               .thickness = 2.0f,
                               .shadow = 24.0f,
                               .startShadow = 0.2,
                               .endShadow = 0.0
                           });
}


void CommandPaletteDraw::process(const OnDraw& draw)
{
    Entity::multiEach<CommandPalette, RenderTransform>([&](ComRef<CommandPalette>, ComRef<RenderTransform> transform)
    {
        draw.draw->pushCommand(std::make_shared<Command>(transform));
    });
}
