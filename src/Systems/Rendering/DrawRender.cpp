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
        colorTargetInfo.clear_color = (SDL_FColor){0.0f, 0.0f, 0.0f, 0.0f};
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

        SDL_GPUTextureTransferInfo transferDest{};
        transferDest.transfer_buffer = draw->dataTransferBuffer;
        transferDest.offset = 0;

        SDL_DownloadFromGPUTexture(pCopyPass, &transferSource, &transferDest);

        SDL_EndGPUCopyPass(pCopyPass);

        const auto pSubmitFence = SDL_SubmitGPUCommandBufferAndAcquireFence(cmdBuf);
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

        SDL_RenderTexture(draw->renderer, draw->outputTexture, nullptr, nullptr);

        SDL_RenderPresent(draw->renderer);

        draw->commands.clear();
    });
}
