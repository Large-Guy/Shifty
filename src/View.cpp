#include "View.h"

View::View(SDL_Renderer *renderer) {
    this->renderer = renderer;
}

void View::setPanel(Panel *panel) {
    this->panel = panel;
}

void View::render() {
    if (texture != nullptr) {
        float textureWidth, textureHeight;
        SDL_GetTextureSize(texture, &textureWidth, &textureHeight);

        float panelWidth, panelHeight;
        panelWidth = panel->renderWidth;
        panelHeight = panel->renderHeight;

        if (panelWidth != textureWidth || panelHeight != textureHeight) {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    }

    if (texture == nullptr) {
        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                                    static_cast<int>(panel->renderWidth), static_cast<int>(panel->renderHeight));
    }

    const SDL_FRect dest = {panel->renderX, panel->renderY, panel->renderWidth, panel->renderHeight};
    SDL_RenderTexture(renderer, texture, nullptr, &dest);
}
