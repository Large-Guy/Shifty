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
            command->execute(draw->renderer);
        }

#ifdef DEBUG
        SDL_RenderDebugText(draw.renderer, 32, 32, debug.c_str());
#endif

        SDL_RenderPresent(draw->renderer);

        draw->commands.clear();
    });
}
