#include "Window.h"

#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <execinfo.h>
#include <SDL3/SDL_init.h>

Window::Window()
{
}

Window::~Window()
{
}

void Window::open()
{
    std::cout << "Creating window ..." << std::endl;
    this->gpuDevice = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_MSL, true, nullptr);
    if (this->gpuDevice == nullptr)
        throw std::runtime_error(std::string("Failed to create GPU device ") + SDL_GetError());

    constexpr int w = 1080, h = 720;
    int flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY;

#ifdef __APPLE__
    flags |= SDL_WINDOW_METAL;
#else
    flags |= SDL_WINDOW_VULKAN;
#endif

    this->window = SDL_CreateWindow("Shifty", w, h, flags);
    if (this->window == nullptr)
        throw std::runtime_error(std::string("Failed to create window") + SDL_GetError());

    if (!SDL_ClaimWindowForGPUDevice(this->gpuDevice, this->window))
        throw std::runtime_error(std::string("Failed to claim window") + SDL_GetError());
}

void Window::close()
{
    SDL_ReleaseWindowFromGPUDevice(this->gpuDevice, this->window);
    SDL_DestroyWindow(this->window);
    SDL_DestroyGPUDevice(this->gpuDevice);

    this->window = nullptr;
    this->gpuDevice = nullptr;
}
