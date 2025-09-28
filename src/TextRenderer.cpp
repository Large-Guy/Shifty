#include "TextRenderer.h"

#include <iostream>
#include <ostream>
#include <ranges>


Font::Font(const std::string& path)
{
    this->path = path;
}

Font::~Font()
{
    for (const auto& val : sizes | std::views::values)
    {
        TTF_CloseFont(val);
    }
}

TTF_Font* Font::size(const float size)
{
    if (!sizes.contains(size))
    {
        sizes[size] = TTF_OpenFont(path.c_str(), size);
    }

    return sizes[size];
}

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

