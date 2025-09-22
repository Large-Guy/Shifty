#include "Text.h"

#include <iostream>
#include <ostream>
#include <ranges>

using namespace Shifty;

Text::FontRegistry::~FontRegistry() {
    for (auto& val: sizes | std::views::values) {
        TTF_CloseFont(val);
    }
}

Text::TextElement::~TextElement() {
    SDL_DestroyTexture(texture);
}

Text::Text(SDL_Renderer* renderer) {
    this->renderer = renderer;
}


void Text::loadFont(const std::string& path, float size) {
    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    if (!font) {
        throw std::runtime_error("Failed to load font");
    }
    fontRegistry[path].sizes[size] = font;
}


void
Text::renderText(const std::string& font, float size, const std::string& text, float x,
                 float y) {
    if (renderer == nullptr) {
        throw std::runtime_error("Renderer is not set");
    }
    float scale;
    SDL_GetRenderScale(renderer, &scale, nullptr);
    float invScale = 1.f / scale;
    size *= scale;

    if (!fontRegistry.contains(font)) {
        loadFont(font, size);
    }
    TTF_Font* f = fontRegistry[font].sizes[size];
    TextRegistry registry{text, f};
    if (!textCache.contains(registry)) {
        TextElement& element = textCache[registry];
        if (!element.texture) {
            SDL_Surface* surface = TTF_RenderText_Blended(fontRegistry[font].sizes[size], text.c_str(), 0,
                                                          {255, 255, 255, 255});
            element.texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_DestroySurface(surface);
        }
    }

    auto* texture = textCache[registry].texture;
    float w, h;
    SDL_GetTextureSize(texture, &w, &h);
    SDL_FRect dest = {x, y, w * invScale, h * invScale};

    SDL_RenderTexture(renderer, texture, nullptr, &dest);
}
