//
// Created by Ravi Lebgue on 10/27/25.
//

#ifndef SHIFTY_TEXTURE_H
#define SHIFTY_TEXTURE_H
#include "Device.h"
#include "SDL3/SDL_gpu.h"

enum class TextureFormat
{
    R8G8B8A8_SRGB,
};

class Texture
{
public:


private:
    SDL_GPUTexture* texture;
    int width, height;
    TextureFormat format;

public:
    Texture(std::shared_ptr<Device> device, int width, int height, TextureFormat format = TextureFormat::R8G8B8A8_SRGB,
            bool renderTarget = false);

    friend class RenderPass;
    friend class Download;
};


#endif //SHIFTY_TEXTURE_H
