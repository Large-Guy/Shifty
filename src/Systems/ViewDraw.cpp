#include "ViewDraw.h"

#include "Components/RenderTransform.h"
#include "Components/Transform.h"
#include "Components/View.h"
#include "ECS/Entity.h"

ViewDrawCommand::ViewDrawCommand(RenderTransform& renderTransform, View& view) : Command(1),
    view(view),
    renderTransform(renderTransform)
{
}

void ViewDrawCommand::execute(SDL_Renderer* renderer)
{
    SDL_FRect rect = {renderTransform.x, renderTransform.y, renderTransform.w, renderTransform.h};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}

DebugRenderTransform::DebugRenderTransform(RenderTransform& renderTransform) : Command(1),
                                                                               renderTransform(renderTransform)
{
}

void DebugRenderTransform::execute(SDL_Renderer* renderer)
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
        draw.draw.pushCommand(std::make_shared<ViewDrawCommand>(transform, view));
    });
}
