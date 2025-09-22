#include "View.h"

#include <utility>

using namespace Shifty;

View::View(SDL_Renderer* renderer, const std::shared_ptr<Layout>& panel) {
    this->renderer = renderer;
    this->panel = panel;
    this->texture = nullptr;
}

void View::setPanel(const std::shared_ptr<Layout>& panel) {
    this->panel = panel;
}

void View::render() {
    if (this->panel == nullptr) {
        throw std::runtime_error("Panel is null");
    }

    SDL_Rect fscreen = {};
    SDL_GetRenderViewport(renderer, &fscreen);

    if (texture != nullptr) {
        float textureWidth, textureHeight;
        SDL_GetTextureSize(texture, &textureWidth, &textureHeight);

        const float panelWidth = panel->renderWidth * static_cast<float>(fscreen.w);
        const float panelHeight = panel->renderHeight * static_cast<float>(fscreen.h);

        if (panelWidth != textureWidth || panelHeight != textureHeight) {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    }

    if (texture == nullptr) {
        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                                    static_cast<int>(panel->renderWidth * static_cast<float>(fscreen.w)),
                                    static_cast<int>(panel->renderHeight * static_cast<float>(fscreen.h)));
    }
    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);


    SDL_SetRenderTarget(renderer, nullptr);


    const SDL_FRect dest = {
            panel->renderX, panel->renderY, panel->renderWidth * static_cast<float>(fscreen.w),
            panel->renderHeight * static_cast<float>(fscreen.h)
    };
    SDL_RenderTexture(renderer, texture, nullptr, &dest);
}
