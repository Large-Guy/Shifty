#include "DrawRender.h"

#include <iostream>

#include "../Components/Draw.h"
#include "../ECS/Entity.h"

void DrawRender::process(const OnRender&)
{
    Entity::each<Draw>([](Draw& draw)
    {
        EventBus::emit(OnDraw{draw});

        //Flush

        SDL_SetRenderDrawColor(draw.renderer, 0, 0, 0, 255);
        SDL_RenderClear(draw.renderer);
        std::string debug = "";
        for (const auto& command : draw.commands)
        {
#ifdef DEBUG
            std::string text = typeid(*command.get()).name();
            debug += text + "\n";
#endif
            command->execute(draw.renderer);
        }

#ifdef DEBUG
        SDL_RenderDebugText(draw.renderer, 32, 32, debug.c_str());
#endif

        SDL_RenderPresent(draw.renderer);

        draw.commands.clear();
    });
}
