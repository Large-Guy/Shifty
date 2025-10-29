#include "TransferBuffer.h"

TransferBuffer::TransferBuffer(std::shared_ptr<Device> device, size_t size)
{
    this->device = device;
    this->size = size;
    SDL_GPUTransferBufferCreateInfo info{};
    info.usage = SDL_GPU_TRANSFERBUFFERUSAGE_DOWNLOAD;
    info.size = size;
    this->buffer = SDL_CreateGPUTransferBuffer(device->device, &info);
}

TransferBuffer::~TransferBuffer()
{
    if (buffer != nullptr)
    {
        SDL_ReleaseGPUTransferBuffer(this->device->device, this->buffer);
    }
}

void* TransferBuffer::map()
{
    return SDL_MapGPUTransferBuffer(device->device, buffer, false);
}

void TransferBuffer::unmap()
{
    SDL_UnmapGPUTransferBuffer(device->device, buffer);
}
