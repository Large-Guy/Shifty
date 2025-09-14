#ifndef SHIFTY_SHIFTYAPP_H
#define SHIFTY_SHIFTYAPP_H
#include <SDL3/SDL.h>

#include "Layout.h"

class ShiftyApp {
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool running;
    std::unique_ptr<Panel> root = std::make_unique<Panel>(Panel::Type::FULL);

public:
    ShiftyApp();

    ~ShiftyApp();

    void run();

    void update();

    void drawPanel(SDL_FRect screen, const std::unique_ptr<Panel> &panel, int depth = 0) const;

    void render() const;
};

#endif //SHIFTY_SHIFTYAPP_H
