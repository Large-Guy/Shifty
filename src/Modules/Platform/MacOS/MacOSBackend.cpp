#include "MacOSBackend.h"
#include "Blur.hpp"

void MacOSBackend::enableBlur(SDL_Window* window)
{
    injectMacVibrancy(window);
}

void MacOSBackend::disableBlur(SDL_Window* window)
{
}

void MacOSBackend::draw(SDL_Window* window, SDL_Renderer* renderer)
{
}

void MacOSBackend::move(SDL_Window* window, int x, int y)
{
}

void MacOSBackend::resize(SDL_Window* window, int width, int height)
{
}


