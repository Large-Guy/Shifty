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
#include "Systems/AnimationUpdate.h"
#include "Systems/AppCreate.h"
#include "Systems/AppUpdate.h"
#include "Systems/ColorRectDraw.h"
#include "Systems/CommandPaletteKeydown.h"
#include "Systems/CommandPaletteUpdate.h"
#include "Systems/DrawCreate.h"
#include "Systems/DrawRender.h"
#include "Systems/OnStart.h"
#include "Systems/RenderTransformsCompute.h"
#include "Systems/TextDraw.h"
#include "Systems/TextEditSystems.h"
#include "Systems/ViewDraw.h"

struct ClearCommand : public Draw::Command
{
    SDL_Color color;

    ClearCommand(SDL_Color color, int priority) : Draw::Command(priority)
    {
        this->color = color;
    }

    void execute(SDL_Renderer* renderer) override
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderClear(renderer);
    }
};

int main(int argc, char* argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        throw std::runtime_error("SDL_Init failed");
    }

    if (!TTF_Init())
    {
        throw std::runtime_error("TTF_Init failed");
    }

    AppCreate appCreate{};
    AppUpdate appUpdate{};

    DrawCreate drawCreate{};
    DrawRender drawRender{};

    AnimationUpdate animationUpdate{};

    //ColorRectDraw colorRectDraw{}; //Debugging purposes

    ViewDraw viewDraw{};
    RenderTransformsCompute renderTransformsCompute{};

    CommandPaletteUpdate commandPaletteUpdate{};
    CommandPaletteKeydown commandPaletteKeydown{};

    TextDraw textDraw{};
    EditInput editInput{};
    EditKeydown editKeydown{};
    EditDraw editDraw{};

    OnStart onStart{};

    EventBus::emit(OnReady{});

    while (Entity::findEntity<App>().get<App>().running)
    {
        EventBus::emit(OnUpdate{
            0.016f
        });
        EventBus::emit(OnRender{});
    }
}
