#include "Texture.h"

#include "SDL3/SDL_gpu.h"

Texture::Texture(std::shared_ptr<Device> device, int width, int height, TextureFormat format, bool renderTarget)
{
    SDL_GPUTextureCreateInfo info{};
    info.type = SDL_GPU_TEXTURETYPE_2D;
    info.format = SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM;
    info.usage = SDL_GPU_TEXTUREUSAGE_COLOR_TARGET | SDL_GPU_TEXTUREUSAGE_SAMPLER;
    info.width = width;
    info.height = height;
    info.layer_count_or_depth = 1;
    info.num_levels = 1;
    info.sample_count = SDL_GPU_SAMPLECOUNT_1;

    this->width = width;
    this->height = height;
    this->format = format;

    texture = SDL_CreateGPUTexture(device->device, &info);
}
