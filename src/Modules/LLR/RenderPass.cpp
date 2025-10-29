#include "RenderPass.h"

RenderPass* RenderPass::current = nullptr;

RenderPass::RenderPass(const std::shared_ptr<Device>& device, std::shared_ptr<Texture> output)
{
    this->info = {};
    info.texture = output->texture;
    info.load_op = SDL_GPU_LOADOP_DONT_CARE;
    info.store_op = SDL_GPU_STOREOP_STORE;
    this->device = device;
}

RenderPass::~RenderPass()
{
    if (this->pass != nullptr)
    {
        end();
    }
}

SDL_GPURenderPass* RenderPass::getPass()
{
    return this->pass;
}


void RenderPass::clear(Color clearColor)
{
    info.load_op = SDL_GPU_LOADOP_CLEAR;
    info.clear_color = {clearColor.r, clearColor.g, clearColor.b, clearColor.a};
}

void RenderPass::viewport(const Viewport& viewport)
{
    this->view = viewport;
}

void RenderPass::begin()
{
    SDL_GPUViewport port{};
    port.x = view.x;
    port.y = view.y;
    port.w = view.w;
    port.h = view.h;
    port.min_depth = view.near;
    port.max_depth = view.far;

    this->pass = SDL_BeginGPURenderPass(device->getCommandBuffer(), &info, 1, nullptr);

    SDL_SetGPUViewport(pass, &port);

    current = this;
}

void RenderPass::end()
{
    if (this->pass == nullptr)
        return;
    SDL_EndGPURenderPass(this->pass);
    this->pass = nullptr;
}
