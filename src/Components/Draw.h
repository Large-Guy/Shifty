#ifndef SHIFTY_DRAW_H
#define SHIFTY_DRAW_H

#include <SDL3/SDL.h>

struct Draw {
    SDL_Renderer *renderer;

    Draw();

    ~Draw();
};


#endif //SHIFTY_DRAW_H
