#ifndef SHIFTY_DOWNLOAD_H
#define SHIFTY_DOWNLOAD_H
#include "Device.h"
#include "Texture.h"
#include "TransferBuffer.h"


class Download
{
    std::shared_ptr<Device> device;
    std::shared_ptr<Texture> source;
    SDL_GPUCopyPass* pass;

public:
    Download(const std::shared_ptr<Device>& device, const std::shared_ptr<Texture>& source);
    ~Download();

    void download(const std::shared_ptr<TransferBuffer>& output);

    void begin();
    void end();
};


#endif //SHIFTY_DOWNLOAD_H
