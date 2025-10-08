#include "DrawCreate.h"

#include <iostream>
#include <stdexcept>

#include "../Components/App.h"

void DrawCreate::process(const OnComponentCreate<Draw>& component)
{
    Entity entity = component.entity;
    auto draw = component.component;
    draw->commands = {};

    if (!entity.has<App>())
    {
        throw std::runtime_error("Entity does not have App!");
    }

    auto app = entity.get<App>();

    int w, h;
    SDL_GetWindowSize(app->window.window, &w, &h);

    //Calculate DPI scale factor
    draw->renderer = SDL_CreateRenderer(app->window.window, nullptr);

    SDL_SetRenderVSync(draw->renderer, SDL_RENDERER_VSYNC_ADAPTIVE);
}
