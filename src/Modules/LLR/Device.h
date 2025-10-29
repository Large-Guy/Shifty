#ifndef SHIFTY_DEVICE_H
#define SHIFTY_DEVICE_H
#include <memory>

#include "SDL3/SDL_gpu.h"


class Device
{
    SDL_GPUDevice* device;
    SDL_GPUCommandBuffer* commandBuffer;

public:
    Device();

    SDL_GPUDevice* getDevice();
    SDL_GPUCommandBuffer* getCommandBuffer();

    void begin();
    void end();
    friend class Texture;
    friend class RenderPass;
    friend class Pipeline;
    friend class Download;
    friend class TransferBuffer;
    friend class Shader;
};


#endif //SHIFTY_DEVICE_H
