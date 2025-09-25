#include "DrawRender.h"

#include "../Components/Draw.h"
#include "../ECS/Entity.h"

void DrawRender::process(const OnRender&) {
    Entity::each<Draw>([](Draw& draw) {
        EventBus::emit(OnDraw{draw});

        //Flush
        SDL_SetRenderDrawColor(draw.renderer, 0, 0, 0, 255);
        SDL_RenderClear(draw.renderer);
        for (const auto& command: draw.commands) {
            command->execute(draw.renderer);
        }

        SDL_RenderPresent(draw.renderer);

        draw.commands.clear();
    });
}
