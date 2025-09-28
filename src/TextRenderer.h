#ifndef SHIFTY_TEXTRENDERER_H
#define SHIFTY_TEXTRENDERER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <SDL3_ttf/SDL_ttf.h>

struct Font
{
    std::string path;
    std::unordered_map<float, TTF_Font*> sizes;

    Font(const std::string& path);
    ~Font();

    TTF_Font* size(float size);
};

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
