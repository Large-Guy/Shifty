#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "ECS/Entity.h"
#include "EventBus.h"
#include "Events.h"

#include "Components/App.h"
#include <iostream>
#include <chrono>

#include "Components/CommandPalette.h"
#include "Events.h"
#include "Components/Draw.h"
#include "Components/InputHandler.h"
#include "Components/Panel.h"
#include "Systems/AnimationUpdate.h"
#include "Systems/AppCreate.h"
#include "Systems/AppUpdate.h"
#include "Systems/Rendering/ColorRectDraw.h"
#include "Systems/CommandPaletteExpansionUpdate.h"
#include "Systems/CommandPaletteUpdate.h"
#include "Systems/DrawCreate.h"
#include "Systems/DrawResize.h"
#include "Systems/FocusUpdate.h"
#include "Systems/MotionUpdate.h"
#include "Systems/Rendering/DrawRender.h"
#include "Systems/TabviewUpdate.h"
#include "Systems/OnStart.h"
#include "Systems/RenderTransformsCompute.h"
#include "Systems/Commands/TabCommand.h"
#include "Systems/Rendering/TextDraw.h"
#include "Systems/TextEditSystems.h"
#include "Systems/PanelAnimationUpdate.h"
#include "Systems/Groups/EditSystemGroup.h"
#include "Systems/Groups/TabViewSystemGroup.h"
#include "Systems/Input/CommandPaletteKeydown.h"
#include "Systems/Input/SelectableMousePress.h"
#include "Systems/Rendering/CommandPaletteDraw.h"
#include "Systems/Rendering/PanelDraw.h"
#include "Systems/Rendering/TabDraw.h"
#include "Systems/Rendering/TabviewDraw.h"

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

    //Create all the systems
    AppCreate appCreate{};
    AppUpdate appUpdate{};

    DrawCreate drawCreate{};
    DrawRender drawRender{};
    DrawResize drawResize{};

    MotionUpdate motionUpdate{};

    FocusUpdate focusUpdate{};

    AnimationUpdate animationUpdate{};

    //ColorRectDraw colorRectDraw{}; //Debugging purposes

    TabDraw viewDraw{};
    PanelDraw panelDraw{};
    PanelAnimationUpdate viewAnimationUpdate{};

    SelectableMousePress selectableMousePress{};

    RenderTransformsCompute renderTransformsCompute{};

    CommandPaletteUpdate commandPaletteUpdate{};
    CommandPaletteKeydown commandPaletteKeydown{};
    CommandPaletteExpansionUpdate commandPaletteExpansion{};
    CommandPaletteDraw commandPaletteDraw{};

    TabViewSystemGroup tabbing{};
    TabviewDraw tabviewDraw{};

    TextDraw textDraw{};

    EditSystemGroup editSystemGroup{};

    OnStart onStart{};

    //Commands
    TabCommand splitCommand{};

    EventBus::emit(OnReady{});

    auto now = std::chrono::high_resolution_clock::now();
    uint64_t previous = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
    uint64_t dt = 16;
    double deltaTime = 0.016;

    while (Entity::findEntity<App>().get<App>()->running)
    {
        EventBus::emit(OnUpdate{
            static_cast<float>(deltaTime)
        });
        EventBus::emit(OnRender{});

        auto current = std::chrono::high_resolution_clock::now();
        uint64_t currentMicros = std::chrono::duration_cast<std::chrono::microseconds>(current.time_since_epoch()).
            count();
        dt = currentMicros - previous;
        previous = currentMicros;
        deltaTime = static_cast<double>(dt) / 1000000.0;
    }
}
