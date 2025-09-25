#include "App.h"

#include <cmath>
#include <iostream>
#include <ostream>
#include <random>

App::App() {
    int w = 1080, h = 720;
    window = SDL_CreateWindow("Shifty", 1080, 720, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
    //Calculate DPI scale factor
    int rw, rh;
    renderer = SDL_CreateRenderer(window, nullptr);
    SDL_GetRenderOutputSize(renderer, &rw, &rh);
    float sw = (float) rw / (float) w;
    float sh = (float) rh / (float) h;
    SDL_SetRenderScale(renderer, sw, sh);

    SDL_SetRenderVSync(renderer, SDL_RENDERER_VSYNC_ADAPTIVE);
}

App::~App() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
