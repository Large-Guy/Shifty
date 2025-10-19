#ifndef SHIFTY_MACOSBACKEND_H
#define SHIFTY_MACOSBACKEND_H
#include "Platform/IBlurManager.h"

class MacOSBackend : public IBlurManager
{
public:
    void enableBlur(SDL_Window* window) override;
    void disableBlur(SDL_Window* window) override;
    void draw(SDL_Window* window, SDL_Renderer* renderer) override;
    void resize(SDL_Window* window, int width, int height) override;
    void move(SDL_Window* window, int x, int y) override;
};


#endif //SHIFTY_MACOSBACKEND_H
