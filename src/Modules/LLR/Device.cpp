#include "Device.h"

#include <stdexcept>
#include <string>

Device::Device()
{
    device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_MSL, true, nullptr);
    if (device == nullptr)
        throw std::runtime_error(std::string("Failed to create GPU device ") + SDL_GetError());
}

SDL_GPUDevice* Device::getDevice()
{
    return this->device;
}

SDL_GPUCommandBuffer* Device::getCommandBuffer()
{
    return this->commandBuffer;
}

void Device::begin()
{
    commandBuffer = SDL_AcquireGPUCommandBuffer(device);
}

void Device::end()
{
    const auto pSubmitFence = SDL_SubmitGPUCommandBufferAndAcquireFence(commandBuffer);
    SDL_WaitForGPUFences(device, true, &pSubmitFence, 1);
    SDL_ReleaseGPUFence(device, pSubmitFence);
    this->commandBuffer = nullptr;
}
