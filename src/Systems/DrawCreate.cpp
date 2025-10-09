#include "DrawCreate.h"

#include <iostream>
#include <stdexcept>

#include "../Components/App.h"

void DrawCreate::process(const OnComponentCreate<Draw>& component)
{
    Entity entity = component.entity;
    auto draw = component.component;
    draw->commands = {};

    if (!entity.has<App>())
    {
        throw std::runtime_error("Entity does not have App!");
    }

    auto app = entity.get<App>();

    int w, h;
    SDL_GetWindowSize(app->window.window, &w, &h);

    //Calculate DPI scale factor
    draw->renderer = SDL_CreateRenderer(app->window.window, nullptr);

    SDL_SetRenderVSync(draw->renderer, SDL_RENDERER_VSYNC_ADAPTIVE);

    draw->gpuDevice = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_MSL, true, nullptr);
    if (draw->gpuDevice == nullptr)
        throw std::runtime_error(std::string("Failed to create GPU device ") + SDL_GetError());


    SDL_GPUTextureCreateInfo info{};
    info.type = SDL_GPU_TEXTURETYPE_2D;
    info.format = SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM;
    info.usage = SDL_GPU_TEXTUREUSAGE_COLOR_TARGET | SDL_GPU_TEXTUREUSAGE_SAMPLER;
    info.width = w;
    info.height = h;
    info.layer_count_or_depth = 1;
    info.num_levels = 1;
    info.sample_count = SDL_GPU_SAMPLECOUNT_1;

    draw->width = w;
    draw->height = h;
    draw->renderTexture = SDL_CreateGPUTexture(draw->gpuDevice, &info);

    SDL_GPUTransferBufferCreateInfo createInfo{};
    createInfo.usage = SDL_GPU_TRANSFERBUFFERUSAGE_DOWNLOAD;
    createInfo.size = draw->width * draw->height * 4;

    draw->dataTransferBuffer = SDL_CreateGPUTransferBuffer(draw->gpuDevice, &createInfo);

    draw->outputTexture = SDL_CreateTexture(draw->renderer, SDL_PIXELFORMAT_RGBA32,
                                            SDL_TEXTUREACCESS_STREAMING, draw->width,
                                            draw->height);
}
