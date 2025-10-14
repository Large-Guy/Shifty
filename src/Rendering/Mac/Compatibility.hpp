#ifndef SHIFTY_VIBRANCY_HPP
#define SHIFTY_VIBRANCY_HPP
#include <SDL3/SDL_video.h>

void* injectMacVibrancy(SDL_Window* window);
void adjustTransparency(void* blurEffect);

#endif //SHIFTY_VIBRANCY_HPP
