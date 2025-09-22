cmake_minimum_required(VERSION 3.5)
cmake_policy(SET CMP0074 NEW)
project(Shifty)

set(CMAKE_CXX_STANDARD 23)

add_executable(Shifty
        src/Main.cpp
        src/ShiftyApp.cpp
        src/ShiftyApp.h
        src/Layout.cpp
        src/Layout.h
        src/Text.cpp
        src/Text.h
        src/View.cpp
        src/View.h
        src/InputHandler.cpp
        src/InputHandler.h
        src/CommandPalette.cpp
        src/CommandPalette.h
        src/Tween.cpp
        src/Tween.h
        src/ECS/Entity.cpp
        src/ECS/Entity.h
)

# Set CEF paths (adjust paths as needed)
set(CEF_ROOT "${CMAKE_SOURCE_DIR}/third_party/cef")

set(CMAKE_FRAMEWORK_PATH "${CMAKE_FRAMEWORK_PATH};~/Library/Frameworks") # Or /Library/Frameworks


list(APPEND CMAKE_MODULE_PATH "${CEF_ROOT}/cmake")

set(CMAKE_PREFIX_PATH "${CEF_ROOT}")

find_package(CEF REQUIRED)
message(STATUS "CEF_BINARY_DIR: ${CEF_BINARY_DIR}")
message(STATUS "CEF_LIBCEF_DLL_WRAPPER_PATH: ${CEF_LIBCEF_DLL_WRAPPER_PATH}")
message(STATUS "CEF_ROOT: ${CEF_ROOT}")
message(STATUS "CEF_TARGET: ${CEF_TARGET}")

get_property(ALL_TARGETS DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY IMPORTED_TARGETS)
message(STATUS "Available targets: ${ALL_TARGETS}")

include("${CEF_ROOT}/cmake/cef_macros.cmake")
include("${CEF_ROOT}/cmake/cef_variables.cmake")

add_subdirectory("${CEF_ROOT}/libcef_dll" libcef_dll)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
find_package(SDL3_image REQUIRED SDL3_image-shared)
find_package(SDL3_ttf REQUIRED SDL3_ttf-shared)

target_link_libraries(Shifty PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_ttf::SDL3_ttf
        libcef_dll_wrapper
)

target_include_directories(Shifty PRIVATE
        ${CEF_ROOT}
)

add_custom_command(TARGET Shifty POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3::SDL3>
        $<TARGET_FILE:SDL3_ttf::SDL3_ttf>
        $<TARGET_FILE:SDL3_image::SDL3_image>
        $<TARGET_FILE_DIR:Shifty>
)
