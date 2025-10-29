#ifndef SHIFTY_BUFFER_H
#define SHIFTY_BUFFER_H
#include <memory>
#include <SDL3/SDL_gpu.h>

#include "Device.h"

class TransferBuffer
{
    std::shared_ptr<Device> device;
    SDL_GPUTransferBuffer* buffer = nullptr;
    size_t size;

public:
    TransferBuffer(std::shared_ptr<Device> device, size_t size);
    ~TransferBuffer();

    void* map();
    void unmap();

    friend class Download;
};


#endif //SHIFTY_BUFFER_H
