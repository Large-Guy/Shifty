#ifndef SHIFTY_FONT_H
#define SHIFTY_FONT_H


#include <memory>
#include <string>
#include <unordered_map>

#include "SDL3_ttf/SDL_ttf.h"

struct Font
{
private:
    static std::unordered_map<std::string, std::shared_ptr<Font>> loaded;

public:
    std::string path;
    std::unordered_map<float, TTF_Font*> sizes;

    Font(const std::string& path);
    ~Font();

    TTF_Font* size(float size);

    static std::shared_ptr<Font> loadPath(const std::string& path);
    static std::shared_ptr<Font> load(const std::string& name);
};

#endif //SHIFTY_FONT_H
