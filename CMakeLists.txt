cmake_minimum_required(VERSION 4.0)
project(Shifty)

set(CMAKE_CXX_STANDARD 23)

add_executable(Shifty
        src/main.cpp
        src/ShiftyApp.cpp
        src/ShiftyApp.h
        src/Layout.cpp
        src/Layout.h)

set(CMAKE_FRAMEWORK_PATH "${CMAKE_FRAMEWORK_PATH};~/Library/Frameworks") # Or /Library/Frameworks

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
find_package(SDL3_image REQUIRED SDL3_image-shared)
find_package(SDL3_ttf REQUIRED SDL3_ttf-shared)
target_link_libraries(Shifty PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf)

add_custom_command(TARGET Shifty POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3::SDL3>
        $<TARGET_FILE:SDL3_ttf::SDL3_ttf>
        $<TARGET_FILE:SDL3_image::SDL3_image>
        $<TARGET_FILE_DIR:Shifty>
)