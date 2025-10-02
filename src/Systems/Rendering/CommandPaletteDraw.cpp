#include "CommandPaletteDraw.h"

#include "Components/CommandPalette.h"

CommandPaletteDraw::Command::Command(ComRef<RenderTransform> transform) : Draw::Command(150)
{
    this->transform = transform;
}

void CommandPaletteDraw::Command::execute(SDL_Renderer* renderer)
{
    SDL_FRect rect = {transform->x, transform->y, transform->w, transform->h};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}


void CommandPaletteDraw::process(const OnDraw& draw)
{
    Entity::multiEach<CommandPalette, RenderTransform>([&](ComRef<CommandPalette>, ComRef<RenderTransform> transform)
    {
        draw.draw->pushCommand(std::make_shared<Command>(transform));
    });
}
