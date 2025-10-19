#include "Font.h"

#include <fontconfig/fontconfig.h>
#include <ranges>

std::unordered_map<std::string, std::shared_ptr<Font>> Font::loaded = {};

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

std::shared_ptr<Font> Font::loadPath(const std::string& path)
{
    if (!loaded.contains(path))
    {
        loaded[path] = std::make_shared<Font>(path);
    }
    return loaded[path];
}

std::shared_ptr<Font> Font::load(const std::string& name)
{
    std::string path = "";

    FcConfig* config = FcInitLoadConfigAndFonts();
    FcPattern* pattern = FcNameParse(reinterpret_cast<const FcChar8*>(name.c_str()));
    FcConfigSubstitute(config, pattern, FcMatchPattern);
    FcDefaultSubstitute(pattern);

    FcResult result;
    FcPattern* match = FcFontMatch(config, pattern, &result);

    FcChar8* file = nullptr;
    if (match && FcPatternGetString(match, FC_FILE, 0, &file) == FcResultMatch)
        path = reinterpret_cast<const char*>(file);

    FcPatternDestroy(match);
    FcPatternDestroy(pattern);
    FcConfigDestroy(config);

    return loadPath(path);
}
