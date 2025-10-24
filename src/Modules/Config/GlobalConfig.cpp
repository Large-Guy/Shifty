#include "GlobalConfig.h"
#include "config_generated.h"

#include <iostream>

#include "SDL3/SDL_filesystem.h"

extern "C" {
#include "sj.h"
}

#include "SDL3/SDL_iostream.h"

namespace fs = std::filesystem;

std::string GlobalConfig::Appearance::theme = "Dark";
std::string GlobalConfig::Appearance::font = "Inter";
float GlobalConfig::Appearance::fontSize = 14.0f;
float GlobalConfig::Appearance::padding = 8.0f;
float GlobalConfig::Appearance::animationSpeed = 1.0f;
bool GlobalConfig::Appearance::transparency = true;
#ifdef __linux__
bool GlobalConfig::Appearance::blur = false; //Defaults to false because of compatibility issues
#else
bool GlobalConfig::Appearance::blur = true;
#endif

int GlobalConfig::TabView::horizontalTabs = 4;
int GlobalConfig::TabView::verticalTabs = 3;

std::filesystem::file_time_type GlobalConfig::lastUpdate = {};


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
            GlobalConfig::Appearance::fontSize = std::atof(val.start);
        }
        else if (eq(key, "padding") && val.type == SJ_NUMBER)
        {
            GlobalConfig::Appearance::padding = std::atof(val.start);
        }
    }
}

static void loadTabview(sj_Reader* r, sj_Value value)
{
    sj_Value key, val;
    while (sj_iter_object(r, value, &key, &val))
    {
        if (eq(key, "horizontalTabs") && val.type == SJ_NUMBER)
        {
            GlobalConfig::TabView::horizontalTabs = std::atoi(val.start);
        }
        else if (eq(key, "verticalTabs") && val.type == SJ_NUMBER)
        {
            GlobalConfig::TabView::verticalTabs = std::atoi(val.start);
        }
    }
}

void GlobalConfig::load()
{
    char* pref = SDL_GetPrefPath("Shifty", "Shifty");
    std::string path = pref;
    SDL_free(pref);
    path += "config.json";

    if (!SDL_GetPathInfo(path.c_str(), nullptr))
    {
        std::cout << "Could not find config file at: " << path << std::endl;
        return;
    }

    auto lastWriteTime = fs::last_write_time(path);

    if (lastWriteTime == lastUpdate)
        return;

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
        }
        else if (eq(key, "tabview") && val.type == SJ_OBJECT)
        {
            loadTabview(&r, val);
        }
    }
}
