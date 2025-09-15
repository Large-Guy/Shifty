#ifndef SHIFTY_TEXT_H
#define SHIFTY_TEXT_H

#include <string>
#include <unordered_map>
#include <vector>
#include <SDL3_ttf/SDL_ttf.h>

/**
 * @class Text
 * @brief Handles caching and rendering text elements, as well as dealing with DPI scaling
 */
class Text {
    struct FontRegistry {
        std::unordered_map<float, TTF_Font*> sizes;

        ~FontRegistry();
    };

    struct TextElement {
        SDL_Texture* texture;

        ~TextElement();
    };

    struct TextRegistry {
        std::string text;
        TTF_Font* font;

        bool operator==(const TextRegistry& other) const {
            return text == other.text && font == other.font;
        }

        size_t hash() const {
            return std::hash<std::string>()(text) ^ std::hash<TTF_Font*>()(font);
        }
    };

    struct TextRegistryHash {
        size_t operator()(const TextRegistry& text) const {
            return text.hash();
        }
    };

    std::unordered_map<std::string, FontRegistry> fontRegistry = {};
    std::unordered_map<TextRegistry, TextElement, TextRegistryHash> textCache = {};

public:
    void loadFont(const std::string& path, float size);

    void
    renderText(SDL_Renderer* renderer, const std::string& font, float size, const std::string& text, float x, float y);
};

#endif //SHIFTY_TEXT_H
