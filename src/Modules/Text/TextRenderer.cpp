#include "TextRenderer.h"

#include <ostream>

SDL_Texture* TextRenderer::getTexture(SDL_Renderer* renderer, TTF_Font* font, const std::string& text)
{
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), text.length(), {255, 255, 255, 255});
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    return texture;
}

void TextRenderer::sizeText(TTF_Font* font, const std::string& text, float* w, float* h)
{
    int width, height;
    TTF_GetStringSize(font, text.c_str(), text.length(), &width, &height);
    *w = static_cast<float>(width);
    *h = static_cast<float>(height);
}

