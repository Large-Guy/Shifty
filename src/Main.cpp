#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "ECS/Entity.h"
#include "Modules/EventBus/EventBus.h"

#include "Modules/Shifty/App/Components/App.h"
#include <chrono>

#include "Config/GlobalConfig.h"
#include "Modules/Drawing/Components/Draw.h"
#include "Drawing/Systems/DrawCreate.h"
#include "Modules/UI/Systems/AnimationUpdate.h"
#include "Modules/Shifty/App/Systems/AppCreate.h"
#include "Modules/Shifty/App/Systems/AppUpdate.h"
#include "Modules/Shifty/CommandPalette/Systems/CommandPaletteExpansionUpdate.h"
#include "Modules/Shifty/CommandPalette/Systems/CommandPaletteUpdate.h"
#include "Modules/Drawing/Systems/DrawResize.h"
#include "Modules/UI/Systems/MotionUpdate.h"
#include "Modules/Drawing/Systems/DrawRender.h"
#include "Modules/Shifty/Tabs/Systems/TabviewUpdate.h"
#include "Modules/Shifty/Systems/OnStart.h"
#include "Modules/UI/Systems/RenderTransformsCompute.h"
#include "Modules/Shifty/Systems/TabCommand.h"
#include "Modules/UI/Systems/TextDraw.h"
#include "Modules/Shifty/Panes/Systems/PaneAnimationUpdate.h"
#include "Modules/Shifty/CommandPalette/Systems/CommandPaletteKeydown.h"
#include "Modules/UI/Systems/SelectableMousePress.h"
#include "Modules/Shifty/CommandPalette/Systems/CommandPaletteDraw.h"
#include "Modules/Shifty/Panes/Systems/PaneDraw.h"
#include "Modules/Shifty/Tabs/Systems/TabDraw.h"
#include "Modules/Shifty/Tabs/Systems/TabviewDraw.h"
#include "SDL3_shadercross/SDL_shadercross.h"
#include "Shifty/App/Systems/AppClose.h"
#include "Shifty/Tabs/Systems/TabviewClick.h"
#include "Shifty/Tabs/Systems/TabviewKeydown.h"
#include "Text/TextRenderer.h"
#include "UI/Systems/FocusUpdate.h"
#include "UI/Systems/TextEditSystems.h"

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

    if (!SDL_ShaderCross_Init())
    {
        throw std::runtime_error("SDL_ShaderCross failed");
    }

    //Create all the systems
    AppCreate appCreate{};
    AppUpdate appUpdate{};
    AppClose appClose{};

    DrawCreate drawCreate{};
    DrawRender drawRender{};
    DrawResize drawResize{};

    MotionUpdate motionUpdate{};

    FocusUpdate focusUpdate{};

    AnimationUpdate animationUpdate{};

    //ColorRectDraw colorRectDraw{}; //Debugging purposes

    TabDraw viewDraw{};

    PaneDraw panelDraw{};
    PaneAnimationUpdate viewAnimationUpdate{};

    SelectableMousePress selectableMousePress{};

    RenderTransformsCompute renderTransformsCompute{};

    CommandPaletteUpdate commandPaletteUpdate{};
    CommandPaletteKeydown commandPaletteKeydown{};
    CommandPaletteExpansionUpdate commandPaletteExpansion{};
    CommandPaletteDraw commandPaletteDraw{};

    TabviewDraw tabviewDraw{};
    TabviewKeydown tabKeydown{};
    TabviewUpdate tabViewUpdate{};
    TabviewClick tabViewClick{};

    TextDraw textDraw{};

    EditProcess editProcess{};
    EditInput editInput{};
    EditKeydown editKeydown{};
    EditDraw editDraw{};

    OnStart onStart{};

    //Commands
    TabCommand splitCommand{};

    EventBus::emit(OnReady{});

    auto now = std::chrono::high_resolution_clock::now();
    uint64_t previous = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
    uint64_t dt = 16;
    double deltaTime = 0.016;

    double configCheckTime = 1.0f;

    while (Entity::findEntity<App>().get<App>()->running)
    {
        configCheckTime += deltaTime;

        if (configCheckTime >= 0.5f)
        {
            configCheckTime = 0.0f;
            GlobalConfig::load();
        }

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
