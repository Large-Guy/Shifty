#include "ViewDraw.h"

#include <iostream>

#include "Components/RenderTransform.h"
#include "Components/Transform.h"
#include "Components/View.h"
#include "ECS/Entity.h"

ViewDraw::Command::Command(RenderTransform& renderTransform, View& view) : Draw::Command(1),
                                                                           view(view),
                                                                           renderTransform(renderTransform)
{
}

void ViewDraw::Command::execute(SDL_Renderer* renderer)
{
    SDL_FRect rect = {renderTransform.x, renderTransform.y, renderTransform.w, renderTransform.h};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}

ViewDraw::DebugRenderTransform::DebugRenderTransform(RenderTransform& renderTransform) : Draw::Command(1),
    renderTransform(renderTransform)
{
}

void ViewDraw::DebugRenderTransform::execute(SDL_Renderer* renderer)
{
    SDL_FRect rect = {renderTransform.x, renderTransform.y, renderTransform.w, renderTransform.h};
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 96);
    SDL_RenderRect(renderer, &rect);
}


void ViewDraw::process(const OnDraw& draw)
{
    Entity::each<RenderTransform>([draw](RenderTransform& transform)
    {
        draw.draw.pushCommand(std::make_shared<DebugRenderTransform>(transform));
    });

    Entity::multiEach<RenderTransform, View>([draw](RenderTransform& transform, View& view)
    {
        draw.draw.pushCommand(std::make_shared<Command>(transform, view));
    });
}
