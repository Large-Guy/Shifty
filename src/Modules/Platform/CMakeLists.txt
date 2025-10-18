if (APPLE)
    set(COMPATIBILITY_SOURCES
            Mac/Compatibility.mm
            Mac/Compatibility.hpp
    )
endif ()

add_library(ShiftyPlatform STATIC
        Window.cpp
        Window.h
        EventHandler.cpp
        EventHandler.h

        ${COMPATIBILITY_SOURCES}
)

target_link_libraries(ShiftyPlatform PUBLIC
        Shifty::Dependencies
        Shifty::EventBus
)

add_library(Shifty::Platform ALIAS ShiftyPlatform)