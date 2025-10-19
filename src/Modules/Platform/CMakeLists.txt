if (APPLE)
    set(COMPATIBILITY_SOURCES
            MacOS/Blur.mm
            MacOS/Blur.hpp
            MacOS/MacOSBackend.cpp
            MacOS/MacOSBackend.h
    )
elseif (LINUX)
    set(COMPATIBILITY_SOURCES
            Linux/Blur.cpp
            Linux/Blur.h
            Linux/LinuxBackend.cpp
            Linux/LinuxBackend.h
    )
endif ()

add_library(ShiftyPlatform STATIC
        Window.cpp
        Window.h
        EventHandler.cpp
        EventHandler.h

        ${COMPATIBILITY_SOURCES}
        IBlurManager.cpp
        IBlurManager.h
)

target_link_libraries(ShiftyPlatform PUBLIC
        Shifty::Dependencies
        Shifty::EventBus
)

add_library(Shifty::Platform ALIAS ShiftyPlatform)