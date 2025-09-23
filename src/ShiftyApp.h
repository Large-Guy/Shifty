#ifndef SHIFTY_SHIFTYAPP_H
#define SHIFTY_SHIFTYAPP_H

#include <SDL3/SDL.h>

#include "Layout.h"
#include "Text.h"
#include "View.h"
#include "InputHandler.h"

namespace Shifty {
    class ShiftyApp {
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        bool running;
        std::vector<std::shared_ptr<Layout> > workspaceRoot = {};
        int currentWorkspace = 0;
        Text text = {nullptr};
        std::vector<View> views = {};

    public:
        ShiftyApp();

        ~ShiftyApp();

        void run();

        void update();

        void drawPanel(SDL_FRect screen, const std::shared_ptr<Layout>& panel, int depth = 0);

        void render();
    };
}

#endif //SHIFTY_SHIFTYAPP_H
