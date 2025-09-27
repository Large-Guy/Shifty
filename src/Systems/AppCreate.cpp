#include "AppCreate.h"

void AppCreate::process(const OnComponentCreate<App>& component) {
    App& app = component.component;

    constexpr int w = 1080, h = 720;
    app.window = SDL_CreateWindow("Shifty", w, h, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
}
