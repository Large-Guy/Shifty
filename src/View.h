#ifndef SHIFTY_VIEW_H
#define SHIFTY_VIEW_H
#include <SDL3/SDL_render.h>

#include "Layout.h"


class View {
    SDL_Renderer *renderer;
    std::shared_ptr<Panel> panel;
    SDL_Texture *texture;

public:
    View(SDL_Renderer *renderer, const std::shared_ptr<Panel> &panel = nullptr);

    void setPanel(const std::shared_ptr<Panel> &panel);

    void render();
};


#endif //SHIFTY_VIEW_H
