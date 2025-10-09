#include "Window.h"

#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <execinfo.h>
#include <SDL3/SDL_init.h>

#ifdef __APPLE__

extern void injectMacVibrancy(SDL_Window* window);

#endif

Window::Window()
{
}

Window::~Window()
{
}

void Window::open()
{
    std::cout << "Creating window ..." << std::endl;

    constexpr int w = 1080, h = 720;

    int flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_TRANSPARENT;

#ifdef __APPLE__
    flags |= SDL_WINDOW_METAL;
#else
    flags |= SDL_WINDOW_VULKAN;
#endif

    this->window = SDL_CreateWindow("Shifty", w, h, flags);
    if (this->window == nullptr)
        throw std::runtime_error(std::string("Failed to create window") + SDL_GetError());

#ifdef __APPLE__
    injectMacVibrancy(this->window);
#endif

    //if (!SDL_ClaimWindowForGPUDevice(this->gpuDevice, this->window))
    //    throw std::runtime_error(std::string("Failed to claim window") + SDL_GetError());
}

void Window::close()
{
    SDL_DestroyWindow(this->window);

    this->window = nullptr;
}
