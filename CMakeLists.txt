cmake_minimum_required(VERSION 4.0)
cmake_policy(SET CMP0074 NEW)
project(Shifty)

set(CMAKE_CXX_STANDARD 23)

set(CORE_SOURCES
        src/Main.cpp
        src/Components/App.h
        src/Components/Layout.h
        src/TextRenderer.cpp
        src/TextRenderer.h
        src/Components/View.h
        src/Components/InputHandler.h
        src/Components/CommandPalette.h
        src/Tween.cpp
        src/Tween.h
        src/ECS/Entity.cpp
        src/ECS/Entity.h
        src/EventBus.cpp
        src/EventBus.h
        src/Events.h
        src/Systems/AppUpdate.cpp
        src/Systems/AppUpdate.h
        src/Components/Draw.h
        src/ECS/Component.cpp
        src/ECS/Component.h
        src/ECS/Type.cpp
        src/ECS/Type.h
        src/ECS/Archetype.cpp
        src/ECS/Archetype.h
        src/ECS/System.cpp
        src/ECS/System.h
        src/Systems/AppCreate.cpp
        src/Systems/AppCreate.h
        src/Systems/DrawCreate.cpp
        src/Systems/DrawCreate.h
        src/Systems/DrawRender.cpp
        src/Systems/DrawRender.h
        src/Systems/OnStart.cpp
        src/Systems/OnStart.h
        src/Systems/ColorRectDraw.cpp
        src/Systems/ColorRectDraw.h
        src/Components/Transform.h
        src/Systems/ViewDraw.cpp
        src/Systems/ViewDraw.h
        src/Components/RenderTransform.h
        src/Systems/RenderTransformsCompute.cpp
        src/Systems/RenderTransformsCompute.h
        src/Systems/CommandPaletteUpdate.cpp
        src/Systems/CommandPaletteUpdate.h
        src/Components/Animation.h
        src/Systems/AnimationUpdate.cpp
        src/Systems/AnimationUpdate.h
        src/Systems/CommandPaletteKeydown.cpp
        src/Systems/CommandPaletteKeydown.h
        src/GlobalConfig.cpp
        src/GlobalConfig.h
        src/Components/Edit.h
        src/Systems/TextEditSystems.cpp
        src/Systems/TextEditSystems.h
        src/Components/Text.h
        src/Systems/TextDraw.cpp
        src/Systems/TextDraw.h
        src/Components/Root.h
        src/Systems/CommandPaletteExpansionUpdate.cpp
        src/Systems/CommandPaletteExpansionUpdate.h
        src/Systems/ViewAnimationUpdate.cpp
        src/Systems/ViewAnimationUpdate.h
        src/Components/Focus.h
        src/Prefabs.cpp
        src/Prefabs.h
        src/Components/Selectable.h
        src/Systems/SelectableMousePress.cpp
        src/Systems/SelectableMousePress.h
        src/Systems/Commands/SplitCommand.cpp
        src/Systems/Commands/SplitCommand.h
        src/Systems/TabViewSystems.cpp
        src/Systems/TabViewSystems.h
        src/Components/TabViewState.h
)

file(GLOB_RECURSE PLUGIN_SOURCES "src/Plugins/**/*.cpp")
file(GLOB_RECURSE PLUGIN_HEADERS "src/Plugins/**/*.h")

add_executable(Shifty
        ${CORE_SOURCES}
        ${PLUGIN_SOURCES}
        ${PLUGIN_HEADERS}
)

set(CMAKE_FRAMEWORK_PATH "${CMAKE_FRAMEWORK_PATH};~/Library/Frameworks") # Or /Library/Frameworks

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
find_package(SDL3_image REQUIRED SDL3_image-shared)
find_package(SDL3_ttf REQUIRED SDL3_ttf-shared)

target_link_libraries(Shifty PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_ttf::SDL3_ttf
)

target_include_directories(Shifty PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

add_custom_command(TARGET Shifty POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3::SDL3>
        $<TARGET_FILE:SDL3_ttf::SDL3_ttf>
        $<TARGET_FILE:SDL3_image::SDL3_image>
        $<TARGET_FILE_DIR:Shifty>
)
