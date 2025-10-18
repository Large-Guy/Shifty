add_library(ShiftyApp STATIC
        Components/App.h
        Systems/AppCreate.cpp
        Systems/AppCreate.h
        Systems/AppUpdate.cpp
        Systems/AppUpdate.h
        Systems/AppClose.cpp
        Systems/AppClose.h
)

target_link_libraries(ShiftyApp PUBLIC
        Shifty::ECS
        Shifty::EventBus
        Shifty::Platform
        Shifty::Drawing
)

add_library(Shifty::App ALIAS ShiftyApp)