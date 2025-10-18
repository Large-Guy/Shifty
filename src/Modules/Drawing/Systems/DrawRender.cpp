#include "DrawRender.h"

#include <iostream>

#include "Drawing/Components/Draw.h"
#include "ECS/Entity.h"
#include "EventBus/EventBus.h"

void DrawRender::process(const OnRender&)
{
    Entity::each<Draw>([](ComRef<Draw> draw)
    {
        EventBus::emit(OnDraw{draw});

        //Handle DPI stuff now in case of monitor change:
        float scale = SDL_GetWindowDisplayScale(SDL_GetRenderWindow(draw->renderer));
        SDL_SetRenderScale(draw->renderer, scale, scale);


        //GPU rendering
        draw->currentCmdBuf = SDL_AcquireGPUCommandBuffer(draw->gpuDevice);
        SDL_GPUColorTargetInfo colorTargetInfo{};
        colorTargetInfo.texture = draw->renderTexture;
        colorTargetInfo.clear_color = (SDL_FColor)
        {
            0.0f, 0.0f, 0.0f, 0.0f
        };
        colorTargetInfo.load_op = SDL_GPU_LOADOP_CLEAR;
        colorTargetInfo.store_op = SDL_GPU_STOREOP_STORE;


        SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(draw->currentCmdBuf, &colorTargetInfo, 1, nullptr);

        draw->currentPass = renderPass;

        SDL_GPUViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.w = draw->width;
        viewport.h = draw->height;
        viewport.min_depth = 0.0f;
        viewport.max_depth = 1.0f;

        SDL_SetGPUViewport(renderPass, &viewport);

        for (const auto& command : draw->commands)
        {
            command->execute(draw->renderer);
        }

        SDL_EndGPURenderPass(renderPass);

        SDL_GPUCopyPass* pCopyPass = SDL_BeginGPUCopyPass(draw->currentCmdBuf);

        SDL_GPUTextureRegion transferSource{};
        transferSource.texture = draw->renderTexture;
        transferSource.w = draw->width;
        transferSource.h = draw->height;
        transferSource.d = 1;

        SDL_GPUTextureTransferInfo transferDest{};
        transferDest.transfer_buffer = draw->dataTransferBuffer;
        transferDest.offset = 0;

        SDL_DownloadFromGPUTexture(pCopyPass, &transferSource, &transferDest);

        SDL_EndGPUCopyPass(pCopyPass);

        const auto pSubmitFence = SDL_SubmitGPUCommandBufferAndAcquireFence(draw->currentCmdBuf);
        SDL_WaitForGPUFences(draw->gpuDevice, true, &pSubmitFence, 1);
        SDL_ReleaseGPUFence(draw->gpuDevice, pSubmitFence);

        auto transferData = SDL_MapGPUTransferBuffer(draw->gpuDevice, draw->dataTransferBuffer, false);
        SDL_UpdateTexture(draw->outputTexture, nullptr, transferData, draw->width * 4);

        // Unmap
        SDL_UnmapGPUTransferBuffer(draw->gpuDevice, draw->dataTransferBuffer);

        SDL_SetRenderDrawBlendMode(draw->renderer, SDL_BLENDMODE_NONE);

        //Flush
#ifdef __APPLE__
        //Apple specific clearing to support macOS Vibrancy
        SDL_SetRenderDrawColor(draw->renderer, 0, 0, 0, 0);
#else

        SDL_SetRenderDrawColor(draw->renderer, 32, 32, 32, 64); //Darken
#endif

        SDL_RenderClear(draw->renderer);

        SDL_RenderTexture(draw->renderer, draw->outputTexture, nullptr, nullptr);

        SDL_RenderPresent(draw->renderer);

        draw->commands.clear();
    });
}
