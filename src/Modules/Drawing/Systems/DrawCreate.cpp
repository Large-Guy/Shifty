#include "DrawCreate.h"

#include <iostream>
#include <stdexcept>

#include "Drawing/Components/Draw.h"
#include "LLR/TransferBuffer.h"
#include "Shifty/App/Components/App.h"

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
    SDL_GetWindowSize(app->window->window, &w, &h);

    //Calculate DPI scale factor
    draw->renderer = SDL_CreateRenderer(app->window->window, nullptr);

    SDL_SetRenderVSync(draw->renderer, SDL_RENDERER_VSYNC_ADAPTIVE);

    draw->device = std::make_shared<Device>();

    draw->width = w;
    draw->height = h;
    draw->renderTexture = std::make_shared<Texture>(draw->device, draw->width, draw->height,
                                                    TextureFormat::R8G8B8A8_SRGB, true);

    draw->transferBuffer = std::make_shared<TransferBuffer>(draw->device, draw->width * draw->height * 4);

    draw->outputTexture = SDL_CreateTexture(draw->renderer, SDL_PIXELFORMAT_RGBA32,
                                            SDL_TEXTUREACCESS_STREAMING, draw->width,
                                            draw->height);

    draw->drawPass = std::make_shared<RenderPass>(draw->device, draw->renderTexture);
}
