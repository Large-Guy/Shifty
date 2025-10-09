//
// Created by Ravi Lebgue on 10/8/25.
//

#ifndef SHIFTY_WINDOW_H
#define SHIFTY_WINDOW_H
#include <SDL3/SDL_gpu.h>


class Window
{
public:
    SDL_Window* window = nullptr;

    Window();
    ~Window();

    void open();
    void close();
};


#endif //SHIFTY_WINDOW_H
