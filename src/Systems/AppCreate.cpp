#include "AppCreate.h"

void AppCreate::process(const OnComponentCreate<App>& component)
{
    auto app = component.component;

    constexpr int w = 1080, h = 720;
    app->window = SDL_CreateWindow("Shifty", w, h,
                                   SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_TRANSPARENT);
    if (app->window == nullptr)
        throw std::runtime_error(std::string("Failed to create window") + SDL_GetError());
    /*
    app->gpuDevice = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV, true, nullptr);
    if (app->gpuDevice == nullptr)
        throw std::runtime_error(std::string("Failed to create GPU device ") + SDL_GetError());*/
}
