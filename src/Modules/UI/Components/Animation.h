#ifndef SHIFTY_ANIMATION_H
#define SHIFTY_ANIMATION_H

#include <string>
#include <unordered_map>


struct Animation
{
    struct Track
    {
        float time = 0.0f;
        float speed = 1.0f;
        bool loop = false;
    };

    std::unordered_map<std::string, Track> tracks = {};

    float operator[](const std::string& name)
    {
        return tracks[name].time;
    }
};


#endif //SHIFTY_ANIMATION_H
