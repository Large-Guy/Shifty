#include "DrawRender.h"

#include <iostream>

#include "../../Components/Draw.h"
#include "../../ECS/Entity.h"

void DrawRender::process(const OnRender&)
{
    Entity::each<Draw>([](ComRef<Draw> draw)
    {
        EventBus::emit(OnDraw{draw});

        //Handle DPI stuff now in case of monitor change:
        float scale = SDL_GetWindowDisplayScale(SDL_GetRenderWindow(draw->renderer));
        SDL_SetRenderScale(draw->renderer, scale, scale);


        //GPU rendering
        SDL_GPUCommandBuffer* cmdBuf = SDL_AcquireGPUCommandBuffer(draw->gpuDevice);
        SDL_GPUColorTargetInfo colorTargetInfo{};
        colorTargetInfo.texture = draw->renderTexture;
        colorTargetInfo.clear_color = (SDL_FColor){1.0f, 0.0f, 1.0f, 0.3f};
        colorTargetInfo.load_op = SDL_GPU_LOADOP_CLEAR;
        colorTargetInfo.store_op = SDL_GPU_STOREOP_STORE;

        SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(cmdBuf, &colorTargetInfo, 1, nullptr);
        SDL_EndGPURenderPass(renderPass);

        SDL_GPUCopyPass* pCopyPass = SDL_BeginGPUCopyPass(cmdBuf);

        SDL_GPUTextureRegion transferSource{};
        transferSource.texture = draw->renderTexture;
        transferSource.w = draw->width;
        transferSource.h = draw->height;
        transferSource.d = 1;

        SDL_GPUTransferBufferCreateInfo createInfo{};
        createInfo.usage = SDL_GPU_TRANSFERBUFFERUSAGE_DOWNLOAD;
        createInfo.size = draw->width * draw->height * 4;

        auto dataTransferBuffer = SDL_CreateGPUTransferBuffer(draw->gpuDevice, &createInfo);

        SDL_GPUTextureTransferInfo transferDest{};
        transferDest.transfer_buffer = dataTransferBuffer;
        transferDest.offset = 0;

        SDL_DownloadFromGPUTexture(pCopyPass, &transferSource, &transferDest);

        SDL_EndGPUCopyPass(pCopyPass);

        const auto pSubmitFence = SDL_SubmitGPUCommandBufferAndAcquireFence(cmdBuf);
        SDL_WaitForGPUFences(draw->gpuDevice, true, &pSubmitFence, 1);
        SDL_ReleaseGPUFence(draw->gpuDevice, pSubmitFence);

        auto transferData = SDL_MapGPUTransferBuffer(draw->gpuDevice, dataTransferBuffer, false);
        SDL_Surface* surface =
            SDL_CreateSurfaceFrom(draw->width, draw->height, SDL_PIXELFORMAT_RGBA32, transferData, draw->width * 4);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(draw->renderer, surface);
        SDL_DestroySurface(surface);

        // Unmap
        SDL_UnmapGPUTransferBuffer(draw->gpuDevice, dataTransferBuffer);

        // Cleanup
        SDL_ReleaseGPUTransferBuffer(draw->gpuDevice, dataTransferBuffer);

        //Flush
        SDL_SetRenderDrawBlendMode(draw->renderer, SDL_BLENDMODE_BLEND);
#ifdef __APPLE__
        //Apple specific clearing to support MacOS Vibrancy
        SDL_SetRenderDrawColor(draw->renderer, 0, 0, 0, 0);
#else
        SDL_SetRenderDrawColor(draw->renderer, 0, 0, 0, 64); //Darken
#endif

        SDL_RenderClear(draw->renderer);
        std::string debug = "";
        for (const auto& command : draw->commands)
        {
#ifdef DEBUG
            std::string text = typeid(*command.get()).name();
            debug += text + "\n";
#endif
            //command->execute(draw->renderer);
        }

#ifdef DEBUG
        SDL_RenderDebugText(draw.renderer, 32, 32, debug.c_str());
#endif

        SDL_RenderTexture(draw->renderer, texture, nullptr, nullptr);

        SDL_RenderPresent(draw->renderer);

        SDL_DestroyTexture(texture);

        draw->commands.clear();
    });
}
