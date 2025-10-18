#include "DrawResize.h"

#include "Drawing/Components/Draw.h"
#include "ECS/Entity.h"

void DrawResize::process(const OnWindowResize& resize)
{
    Entity::each<Draw>([resize](ComRef<Draw> draw)
                       {
                           draw->width = resize.width;
                           draw->height = resize.height;

                           //release old data
                           SDL_ReleaseGPUTransferBuffer(draw->gpuDevice, draw->dataTransferBuffer);
                           SDL_ReleaseGPUTexture(draw->gpuDevice, draw->renderTexture);

                           SDL_GPUTextureCreateInfo info{};
                           info.type = SDL_GPU_TEXTURETYPE_2D;
                           info.format = SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM;
                           info.usage = SDL_GPU_TEXTUREUSAGE_COLOR_TARGET | SDL_GPU_TEXTUREUSAGE_SAMPLER;
                           info.width = resize.width;
                           info.height = resize.height;
                           info.layer_count_or_depth = 1;
                           info.num_levels = 1;
                           info.sample_count = SDL_GPU_SAMPLECOUNT_1;

                           draw->width = resize.width;
                           draw->height = resize.height;
                           draw->renderTexture = SDL_CreateGPUTexture(draw->gpuDevice, &info);

                           SDL_GPUTransferBufferCreateInfo createInfo{};
                           createInfo.usage = SDL_GPU_TRANSFERBUFFERUSAGE_DOWNLOAD;
                           createInfo.size = draw->width * draw->height * 4;

                           draw->dataTransferBuffer = SDL_CreateGPUTransferBuffer(draw->gpuDevice, &createInfo);

                           draw->outputTexture = SDL_CreateTexture(draw->renderer, SDL_PIXELFORMAT_RGBA32,
                                                                   SDL_TEXTUREACCESS_STREAMING, draw->width,
                                                                   draw->height);
                       },
                       [resize](ComRef<Draw> draw)
                       {
                           return SDL_GetRenderWindow(draw->renderer) == resize.window;
                       });
}