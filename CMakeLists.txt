cmake_minimum_required(VERSION 4.0)
cmake_policy(SET CMP0074 NEW)

if (APPLE)
    project(Shifty LANGUAGES C CXX OBJCXX)
else ()
    project(Shifty LANGUAGES C CXX)
endif ()
set(CMAKE_CXX_STANDARD 23)

#include directories

include_directories(
        ${CMAKE_SOURCE_DIR}/src/Modules
)

# External dependencies
add_subdirectory(external)

add_subdirectory(src/Modules/ECS)
add_subdirectory(src/Modules/Hierarchy)
add_subdirectory(src/Modules/EventBus)
add_subdirectory(src/Modules/Platform)
add_subdirectory(src/Modules/LLR)
add_subdirectory(src/Modules/Drawing)
add_subdirectory(src/Modules/UI)
add_subdirectory(src/Modules/Shifty)

set(CORE_SOURCES
        src/Main.cpp
)


add_executable(Shifty
        ${CORE_SOURCES}
)

target_link_libraries(Shifty PRIVATE
        Shifty::Dependencies
        Shifty::ECS
        Shifty::LLR
        Shifty::Drawing
        Shifty::Platform
        Shifty::EventBus
        Shifty::UI
        Shifty::Shifty
)


add_custom_command(TARGET Shifty POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3::SDL3>
        $<TARGET_FILE:SDL3_ttf::SDL3_ttf>
        $<TARGET_FILE:SDL3_image::SDL3_image>
        $<TARGET_FILE_DIR:Shifty>
)
