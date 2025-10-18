#include "Window.h"

#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <execinfo.h>
#include "SDL3/SDL_init.h"

#include "LLR/Mac/Compatibility.hpp"

Window::Window(const std::string& name, int width, int height)
{
    std::cout << "Creating window ..." << std::endl;
    int flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_TRANSPARENT;

#ifdef __APPLE__
    flags |= SDL_WINDOW_METAL;
#else
    flags |= SDL_WINDOW_VULKAN;
#endif

    this->window = SDL_CreateWindow(name.c_str(), width, height, flags);
    if (this->window == nullptr)
        throw std::runtime_error(std::string("Failed to create window") + SDL_GetError());

#ifdef __APPLE__
    injectMacVibrancy(this->window);
#endif
}

Window::~Window()
{
    if (this->window != nullptr)
        SDL_DestroyWindow(this->window);

    this->window = nullptr;
}
