#include "DrawCreate.h"

#include <stdexcept>

#include "../Components/App.h"

void DrawCreate::process(const OnComponentCreate<Draw>& component) {
    Entity entity = component.entity;
    Draw& draw = component.component;
    draw.commands = {};

    if (!entity.has<App>()) {
        throw std::runtime_error("Entity does not have App!");
    }

    App& app = entity.get<App>();

    int w, h;
    SDL_GetWindowSize(app.window, &w, &h);

    //Calculate DPI scale factor
    int rw, rh;
    draw.renderer = SDL_CreateRenderer(app.window, nullptr);
    SDL_GetRenderOutputSize(draw.renderer, &rw, &rh);
    float sw = (float) rw / (float) w;
    float sh = (float) rh / (float) h;
    SDL_SetRenderScale(draw.renderer, sw, sh);

    SDL_SetRenderVSync(draw.renderer, SDL_RENDERER_VSYNC_ADAPTIVE);
}
