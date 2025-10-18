add_library(ShiftyShifty STATIC
        Systems/OnStart.cpp
        Systems/OnStart.h
        Systems/TabCommand.cpp
        Systems/TabCommand.h
)

add_subdirectory(App)
add_subdirectory(CommandPalette)
add_subdirectory(Panes)
add_subdirectory(Tabs)

target_link_libraries(ShiftyShifty PUBLIC
        Shifty::Dependencies
        Shifty::ECS
        Shifty::Hierarchy
        Shifty::EventBus
        Shifty::Platform
        Shifty::LLR
        Shifty::Drawing
        Shifty::UI

        Shifty::App
        Shifty::CommandPalette
        Shifty::Panes
        Shifty::Tabs
)

add_library(Shifty::Shifty ALIAS ShiftyShifty)