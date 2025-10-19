add_library(ShiftyPanes STATIC
        Components/Pane.h
        Components/Root.h
        Systems/PaneAnimationUpdate.cpp
        Systems/PaneAnimationUpdate.h
        Systems/PaneDraw.cpp
        Systems/PaneDraw.h
        Prefab.cpp
        Prefab.h
)

target_link_libraries(ShiftyPanes PUBLIC
        Shifty::ECS
        Shifty::EventBus
        Shifty::Drawing
        Shifty::Hierarchy
        Shifty::Config
)

add_library(Shifty::Panes ALIAS ShiftyPanes)