#include "DrawRender.h"

#include "../Components/Draw.h"
#include "../ECS/Entity.h"

void DrawRender::process(const OnRender &) {
    Entity::each<Draw>([](Draw &draw) {
        //Flush
        for (const auto &command: draw.commands) {
            command->execute(draw.renderer);
        }

        SDL_RenderPresent(draw.renderer);

        draw.commands.clear();
    });
}
