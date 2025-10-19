#include "LinuxBackend.h"

#include "SDL3/SDL_messagebox.h"

bool LinuxBackend::isWayland()
{
    return getenv("WAYLAND_DISPLAY") != NULL;
}

bool LinuxBackend::isX11()
{
    return getenv("DISPLAY") != NULL && !isWayland();
}

LinuxBackend::Protocol LinuxBackend::getBackend()
{
    if (isWayland())
    {
        return Protocol::WAYLAND;
    }

    if (isX11())
    {
        return Protocol::X11;
    }

    return Protocol::UNKNOWN;
}

void LinuxBackend::enableBlur(SDL_Window* window)
{
    this->backend = getBackend();

    if (this->backend == Protocol::UNKNOWN || this->backend == Protocol::WAYLAND)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Blur Not Supported",
                                 "Blur is not supported on Wayland or unknown display protocols on Linux.",
                                 nullptr);
    }
}

void LinuxBackend::disableBlur(SDL_Window* window)
{
}

void LinuxBackend::draw(SDL_Window* window, SDL_Renderer* renderer)
{
}

void LinuxBackend::resize(SDL_Window* window, int width, int height)
{
}

void LinuxBackend::move(SDL_Window* window, int x, int y)
{
}
