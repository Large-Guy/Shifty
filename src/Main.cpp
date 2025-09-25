#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "ECS/Entity.h"
#include "EventBus.h"
#include "Events.h"

#include "Components/App.h"
#include <iostream>

#include "Components/CommandPalette.h"
#include "Events.h"
#include "Components/Draw.h"
#include "Components/InputHandler.h"
#include "Components/View.h"
#include "Systems/AppCreate.h"
#include "Systems/AppUpdate.h"
#include "Systems/DrawCreate.h"
#include "Systems/DrawRender.h"

struct ClearCommand : public Draw::Command {
    SDL_Color color;

    ClearCommand(SDL_Color color, int priority) : Draw::Command(priority) {
        this->color = color;
    }

    void execute(SDL_Renderer *renderer) override {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderClear(renderer);
    }
};

int main(int argc, char *argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error("SDL_Init failed");
    }

    if (!TTF_Init()) {
        throw std::runtime_error("TTF_Init failed");
    }

    AppCreate appCreate{};
    AppUpdate appUpdate{};

    DrawCreate drawCreate{};
    DrawRender drawRender{};

    EventBus::subscribe<OnReady>([](const OnReady &e) {
        Entity world = Entity::create();
        world.add<InputHandler>();
        world.add<App>();
        world.add<Draw>();

        /*
        Entity root = Entity::create();
        root.add<Layout>();
        root.add<View>();
        root.add<CommandPalette>();
        */
    });

    EventBus::subscribe<OnRender>([](const OnRender &e) {
        Entity::each<CommandPalette>([](Entity entity, CommandPalette &view) {
            if (view.open) {
                auto &layout = entity.get<Layout>();
            }
        });

        Entity::each<Draw>([](Entity entity, Draw &draw) {
            draw.pushCommand(std::make_shared<ClearCommand>(SDL_Color{255, 0, 0, 255}, 0));

            draw.pushCommand(std::make_shared<ClearCommand>(SDL_Color{0, 255, 0}, 100));
        });
    });

    EventBus::emit(OnReady{});

    while (Entity::find<App>().get<App>().running) {
        EventBus::emit(OnUpdate{
            0.016f
        });
        EventBus::emit(OnRender{});
    }
}
