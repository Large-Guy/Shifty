add_library(ShiftyText STATIC
        TextRenderer.h
        TextRenderer.cpp
        Font.cpp
        Font.h
)

set(COMPATIBILITY_LIBRARIES "")

if (UNIX AND NOT APPLE)
    find_package(Fontconfig REQUIRED)
    list(APPEND COMPATIBILITY_LIBRARIES Fontconfig::Fontconfig)
elseif (APPLE)
    # idk how to do this on macOS yet
else (WINDOWS)
    # idk how to do this on Windows yet
endif ()

target_link_libraries(ShiftyText PUBLIC
        Shifty::Dependencies
        Shifty::LLR
        Shifty::Config
        ${COMPATIBILITY_LIBRARIES}
)

add_library(Shifty::Text ALIAS ShiftyText)