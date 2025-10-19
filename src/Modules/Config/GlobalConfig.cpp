#include "GlobalConfig.h"

#include <iostream>

extern "C" {
#include "sj.h"
}

#include "SDL3/SDL_iostream.h"

std::string GlobalConfig::Appearance::theme = "Dark";
std::string GlobalConfig::Appearance::font = "Inter";
float GlobalConfig::Appearance::fontSize = 14.0f;
float GlobalConfig::Appearance::padding = 16.0f;
float GlobalConfig::Appearance::animationSpeed = 1.0f;
bool GlobalConfig::Appearance::transparency = true;
bool GlobalConfig::Appearance::blur;

int GlobalConfig::TabView::horizontalTabs = 4;
int GlobalConfig::TabView::verticalTabs = 3;


static bool eq(sj_Value val, const char* s)
{
    size_t len = val.end - val.start;
    return len == strlen(s) && !memcmp(val.start, s, len);
}

static void loadAppearance(sj_Reader* r, sj_Value value)
{
    sj_Value key, val;
    while (sj_iter_object(r, value, &key, &val))
    {
        if (eq(key, "theme") && val.type == SJ_STRING)
        {
            GlobalConfig::Appearance::theme = std::string(val.start, (size_t)val.end - (size_t)val.start);
        }
        else if (eq(key, "font") && val.type == SJ_STRING)
        {
            GlobalConfig::Appearance::font = std::string(val.start, (size_t)val.end - (size_t)val.start);
        }
        else if (eq(key, "fontSize") && val.type == SJ_NUMBER)
        {
            GlobalConfig::Appearance::fontSize = atof(val.start);
        }
        else if (eq(key, "padding") && val.type == SJ_NUMBER)
        {
            GlobalConfig::Appearance::padding = atof(val.start);
        }
    }
}

void GlobalConfig::load(const std::string& path)
{
    size_t len;
    auto* configFile = static_cast<char*>(SDL_LoadFile(path.c_str(), &len));

    sj_Reader r = sj_reader(configFile, len);
    sj_Value rootObj = sj_read(&r);

    sj_Value key, val;
    while (sj_iter_object(&r, rootObj, &key, &val))
    {
        if (eq(key, "appearance") && val.type == SJ_OBJECT)
        {
            loadAppearance(&r, val);
            continue;
        }
    }
}
