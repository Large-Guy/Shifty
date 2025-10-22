set(SDLSHADERCROSS_VENDORED ON)

add_subdirectory(SDL)
add_subdirectory(SDL_image)
add_subdirectory(SDL_ttf)
add_subdirectory(SDL_shadercross)

set(CMAKE_FRAMEWORK_PATH "${CMAKE_FRAMEWORK_PATH};~/Library/Frameworks") # Or /Library/Frameworks

if (APPLE)
    find_library(COCOA_FRAMEWORK Cocoa)
endif ()

add_library(sj STATIC
        sj.h/sj.h
        sj.c
)

add_library(ShiftyDependencies INTERFACE)
target_link_libraries(ShiftyDependencies INTERFACE SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf SDL3_shadercross::SDL3_shadercross sj ${COCOA_FRAMEWORK})

include_directories(
        ${CMAKE_SOURCE_DIR}/external
        ${CMAKE_SOURCE_DIR}/external/SDL3/include
        ${CMAKE_SOURCE_DIR}/external/SDL3_ttf/include
        ${CMAKE_SOURCE_DIR}/external/SDL3_image/include
        ${CMAKE_SOURCE_DIR}/external/SDL_shadercross/include
)

add_library(Shifty::Dependencies ALIAS ShiftyDependencies)