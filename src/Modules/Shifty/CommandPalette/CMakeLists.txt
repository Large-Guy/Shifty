add_library(ShiftyCommandPalette STATIC
        Components/CommandPalette.h
        Systems/CommandPaletteDraw.cpp
        Systems/CommandPaletteDraw.h
        Systems/CommandPaletteExpansionUpdate.cpp
        Systems/CommandPaletteExpansionUpdate.h
        Systems/CommandPaletteKeydown.cpp
        Systems/CommandPaletteKeydown.h
        Systems/CommandPaletteUpdate.cpp
        Systems/CommandPaletteUpdate.h
)

target_link_libraries(ShiftyCommandPalette PUBLIC
        Shifty::ECS
        Shifty::EventBus
        Shifty::UI
        Shifty::Platform
        Shifty::Drawing
)

add_library(Shifty::CommandPalette ALIAS ShiftyCommandPalette)