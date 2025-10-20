#ifndef SHIFTY_GLOBALCONFIG_H
#define SHIFTY_GLOBALCONFIG_H
#include <string>
#include <chrono>
#include <filesystem>

struct GlobalConfig
{
    struct Appearance
    {
        //General
        static std::string theme;
        static std::string font;
        static float fontSize;
        static float padding;
        static float animationSpeed;
        static bool transparency;
        static bool blur;
    };

    struct TabView
    {
        static int horizontalTabs;
        static int verticalTabs;
    };

    static std::filesystem::file_time_type lastUpdate;

    static void load();
};


#endif //SHIFTY_GLOBALCONFIG_H
