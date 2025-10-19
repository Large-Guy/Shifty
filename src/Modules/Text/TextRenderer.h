#ifndef SHIFTY_TEXTRENDERER_H
#define SHIFTY_TEXTRENDERER_H

#include <memory>
#include <string>

#include "SDL3_ttf/SDL_ttf.h"


/**
 * @class TextRenderer
 * @brief Handles caching and rendering text elements, as well as dealing with DPI scaling
 */
class TextRenderer
{
public:
    static SDL_Texture* getTexture(SDL_Renderer* renderer, TTF_Font* font, const std::string& text);
    static void sizeText(TTF_Font* font, const std::string& text, float* w, float* h);
};

#endif //SHIFTY_TEXTRENDERER_H
