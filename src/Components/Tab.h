#ifndef SHIFTY_TAB_H
#define SHIFTY_TAB_H
#include <string>
#include <SDL3/SDL_render.h>

struct Tab
{
    std::string url;
    SDL_Texture* page;
    Entity viewer;
};

#endif //SHIFTY_TAB_H
