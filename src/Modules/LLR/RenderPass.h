#ifndef SHIFTY_RENDERPASS_H
#define SHIFTY_RENDERPASS_H
#include <memory>

#include "Color.h"
#include "Device.h"
#include "Texture.h"
#include "Viewport.h"
#include "SDL3/SDL_gpu.h"


class RenderPass
{
    static RenderPass* current;
    SDL_GPURenderPass* pass = nullptr;
    Viewport view;
    SDL_GPUColorTargetInfo info;
    std::shared_ptr<Device> device;

public:
    RenderPass(const std::shared_ptr<Device>& device, std::shared_ptr<Texture> output);
    ~RenderPass();

    SDL_GPURenderPass* getPass();

    void clear(Color clearColor);
    void viewport(const Viewport& viewport);

    void begin();

    void end();

    friend class Pipeline;
};


#endif //SHIFTY_RENDERPASS_H
