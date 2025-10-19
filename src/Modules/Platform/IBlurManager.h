#ifndef SHIFTY_IBLURMANAGER_H
#define SHIFTY_IBLURMANAGER_H
#include "SDL3/SDL_render.h"

class IBlurManager
{
public:
    virtual ~IBlurManager() = default;
    virtual void enableBlur(SDL_Window* window) = 0;
    virtual void disableBlur(SDL_Window* window) = 0;
    virtual void draw(SDL_Window* window, SDL_Renderer* renderer) = 0;
    virtual void resize(SDL_Window* window, int width, int height) = 0;
    virtual void move(SDL_Window* window, int x, int y) = 0;
};


#endif //SHIFTY_IBLURMANAGER_H
