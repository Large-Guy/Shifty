#ifndef SHIFTY_TEXT_H
#define SHIFTY_TEXT_H
#include <string>

#include "TextRenderer.h"


struct Text
{
    enum class Alignment
    {
        Leading,
        Center,
        Trailing,
    };

    Alignment horizontal = Alignment::Leading;
    Alignment vertical = Alignment::Center;
    std::string text;
    std::shared_ptr<Font> font;
    float size;

    std::string rendered;
    SDL_Texture* texture;
};


#endif //SHIFTY_TEXT_H
