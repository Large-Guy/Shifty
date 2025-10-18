add_library(ShiftyPlatform STATIC
        Window.cpp
        Window.h
        EventHandler.cpp
        EventHandler.h
)

target_link_libraries(ShiftyPlatform PUBLIC
        Shifty::Dependencies
        Shifty::EventBus
)

add_library(Shifty::Platform ALIAS ShiftyPlatform)