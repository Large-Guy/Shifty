//
// Created by Ravi Lebgue on 9/25/25.
//

#include "ColorRectDraw.h"

#include "../ECS/Entity.h"

RectCommand::RectCommand(int priority, SDL_FRect& rect, SDL_Color& color) : rect(rect), color(color),
                                                                            Command(priority) {
}


void RectCommand::execute(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderRect(renderer, &rect);
}


void ColorRectDraw::process(const OnDraw& onDraw) {
    Entity::multiEach<SDL_FRect, SDL_Color>([onDraw](SDL_FRect& rect, SDL_Color& color) {
        onDraw.draw.pushCommand(std::make_shared<RectCommand>(1, rect, color));
    });
}
