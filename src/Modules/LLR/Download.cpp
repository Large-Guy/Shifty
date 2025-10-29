#include "Download.h"

Download::Download(const std::shared_ptr<Device>& device, const std::shared_ptr<Texture>& source)
{
    this->device = device;
    this->source = source;
}

Download::~Download()
{
    end();
}

void Download::download(const std::shared_ptr<TransferBuffer>& output)
{
    SDL_GPUTextureRegion transferSource{};
    transferSource.texture = source->texture;
    transferSource.w = source->width;
    transferSource.h = source->height;
    transferSource.d = 1;

    SDL_GPUTextureTransferInfo transferDest{};
    transferDest.transfer_buffer = output->buffer;
    transferDest.offset = 0;

    SDL_DownloadFromGPUTexture(this->pass, &transferSource, &transferDest);
}

void Download::begin()
{
    auto buffer = device->getCommandBuffer();
    this->pass = SDL_BeginGPUCopyPass(buffer);
}

void Download::end()
{
    if (pass == nullptr)
        return;
    SDL_EndGPUCopyPass(pass);
    pass = nullptr;
}
