add_library(ShiftyDrawing STATIC
        Components/Draw.h
        Components/RenderTransform.h
        Systems/DrawCreate.cpp
        Systems/DrawCreate.h
        Systems/DrawRender.cpp
        Systems/DrawRender.h
        Systems/DrawResize.cpp
        Systems/DrawResize.h
        Systems/DrawSystem.cpp
        Systems/DrawSystem.h
        Tween.cpp
        Tween.h
)

target_link_libraries(ShiftyDrawing PUBLIC
        Shifty::Dependencies
        Shifty::LLR
        Shifty::ECS
        Shifty::EventBus
        Shifty::Config
)

add_library(Shifty::Drawing ALIAS ShiftyDrawing)