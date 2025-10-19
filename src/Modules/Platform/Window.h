#ifndef SHIFTY_WINDOW_H
#define SHIFTY_WINDOW_H
#include <string>

#include "EventHandler.h"
#include "IBlurManager.h"

class Window
{
public:
    SDL_Window* window = nullptr;
    std::unique_ptr<IBlurManager> blur;

    Window() = default;
    Window(const std::string& name, int width, int height);
    ~Window();
};


#endif //SHIFTY_WINDOW_H
