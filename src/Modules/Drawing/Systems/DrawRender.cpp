#include "DrawRender.h"

#include <iostream>

#include "Drawing/Components/Draw.h"
#include "ECS/Entity.h"
#include "EventBus/EventBus.h"
#include "LLR/Download.h"

void DrawRender::process(const OnRender&)
{
    Entity::each<Draw>([](ComRef<Draw> draw)
    {
        EventBus::emit(OnDraw{draw});

        //Handle DPI stuff now in case of monitor change:
        float scale = SDL_GetWindowDisplayScale(SDL_GetRenderWindow(draw->renderer));
        SDL_SetRenderScale(draw->renderer, scale, scale);

        draw->device->begin();

        //GPU rendering
        draw->drawPass->clear({0.0f, 0.0f, 0.0f, 0.0f});
        draw->drawPass->viewport({
            0.0f, 0.0f, static_cast<float>(draw->width), static_cast<float>(draw->height), 0.0f, 1.0f
        });
        draw->drawPass->begin();


        for (const auto& command : draw->commands)
        {
            command->execute(draw->renderer);
        }

        draw->drawPass->end();

        std::shared_ptr<Download> download = std::make_shared<Download>(draw->device, draw->renderTexture);
        download->begin();

        download->download(draw->transferBuffer);

        download->end();

        draw->device->end();

        auto transferData = draw->transferBuffer->map();
        SDL_UpdateTexture(draw->outputTexture, nullptr, transferData, draw->width * 4);
        // Unmap
        draw->transferBuffer->unmap();

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
