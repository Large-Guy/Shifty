#include "ViewDraw.h"

#include "Components/RenderTransform.h"
#include "Components/Transform.h"
#include "Components/View.h"
#include "ECS/Entity.h"

ViewDrawCommand::ViewDrawCommand(RenderTransform& renderTransform, View& view) : Command(1),
    view(view),
    renderTransform(renderTransform) {
}

void ViewDrawCommand::execute(SDL_Renderer* renderer) {
    SDL_FRect rect = {renderTransform.x, renderTransform.y, renderTransform.w, renderTransform.h};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}


void ViewDraw::process(const OnDraw& draw) {
    Entity::multiEach<RenderTransform, View>([draw](RenderTransform& transform, View& view) {
        draw.draw.pushCommand(std::make_shared<ViewDrawCommand>(transform, view));
    });
}

