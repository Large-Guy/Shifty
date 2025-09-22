#ifndef SHIFTY_COMMANDPALETTE_H
#define SHIFTY_COMMANDPALETTE_H


#include <SDL3/SDL.h>
#include "Layout.h"

namespace Shifty {

    class CommandPalette {
    private:
        bool isOpen = false;
        SDL_Renderer* renderer = nullptr;
        float openTime = 0;
    public:
        Layout layout;

        void open();

        void close();

        void update();

        void render();
    };

}

#endif //SHIFTY_COMMANDPALETTE_H
