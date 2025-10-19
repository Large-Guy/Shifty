#ifndef SHIFTY_GLOBALCONFIG_H
#define SHIFTY_GLOBALCONFIG_H
#include <string>

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

    static void load(const std::string& path);
};


#endif //SHIFTY_GLOBALCONFIG_H
