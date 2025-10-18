add_subdirectory(SDL)
add_subdirectory(SDL_image)
add_subdirectory(SDL_ttf)

set(CMAKE_FRAMEWORK_PATH "${CMAKE_FRAMEWORK_PATH};~/Library/Frameworks") # Or /Library/Frameworks

if (APPLE)
    find_library(COCOA_FRAMEWORK Cocoa)
endif ()

add_library(ShiftyDependencies INTERFACE)
target_link_libraries(ShiftyDependencies INTERFACE SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf ${COCOA_FRAMEWORK})

include_directories(
        ${CMAKE_SOURCE_DIR}/external/SDL3/include
        ${CMAKE_SOURCE_DIR}/external/SDL3_ttf/include
        ${CMAKE_SOURCE_DIR}/external/SDL3_image/include
)

add_library(Shifty::Dependencies ALIAS ShiftyDependencies)