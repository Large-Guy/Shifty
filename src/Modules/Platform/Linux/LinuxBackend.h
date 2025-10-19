#ifndef SHIFTY_LINUXBACKEND_H
#define SHIFTY_LINUXBACKEND_H
#include <string>

#include "Platform/IBlurManager.h"


/**
 * Linux blur backend uses a hacky implementation since Wayland does not provide proper blur support
 */
class LinuxBackend : public IBlurManager
{
public:
    enum class Protocol
    {
        WAYLAND,
        X11,
        UNKNOWN
    };

    Protocol backend;

    bool isWayland();
    bool isX11();
    Protocol getBackend();
    void enableBlur(SDL_Window* window) override;
    void disableBlur(SDL_Window* window) override;
    void draw(SDL_Window* window, SDL_Renderer* renderer) override;
    void resize(SDL_Window* window, int width, int height) override;
    void move(SDL_Window* window, int x, int y) override;
};


#endif //SHIFTY_LINUXBACKEND_H
