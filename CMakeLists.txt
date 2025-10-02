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
        src/Components/Panel.h
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
        src/Systems/Rendering/DrawRender.cpp
        src/Systems/Rendering/DrawRender.h
        src/Systems/OnStart.cpp
        src/Systems/OnStart.h
        src/Systems/Rendering/ColorRectDraw.cpp
        src/Systems/Rendering/ColorRectDraw.h
        src/Components/Transform.h
        src/Systems/Rendering/TabDraw.cpp
        src/Systems/Rendering/TabDraw.h
        src/Components/RenderTransform.h
        src/Systems/RenderTransformsCompute.cpp
        src/Systems/RenderTransformsCompute.h
        src/Systems/CommandPaletteUpdate.cpp
        src/Systems/CommandPaletteUpdate.h
        src/Components/Animation.h
        src/Systems/AnimationUpdate.cpp
        src/Systems/AnimationUpdate.h
        src/GlobalConfig.cpp
        src/GlobalConfig.h
        src/Components/Edit.h
        src/Systems/TextEditSystems.cpp
        src/Systems/TextEditSystems.h
        src/Components/Text.h
        src/Systems/Rendering/TextDraw.cpp
        src/Systems/Rendering/TextDraw.h
        src/Components/Root.h
        src/Systems/CommandPaletteExpansionUpdate.cpp
        src/Systems/CommandPaletteExpansionUpdate.h
        src/Systems/ViewAnimationUpdate.cpp
        src/Systems/ViewAnimationUpdate.h
        src/Components/Focus.h
        src/Prefabs.cpp
        src/Prefabs.h
        src/Components/Selectable.h
        src/Systems/Commands/TabCommand.cpp
        src/Systems/Commands/TabCommand.h
        src/Systems/TabViewUpdate.cpp
        src/Systems/TabViewUpdate.h
        src/Components/TabViewState.h
        src/Components/Tab.h
        src/Systems/Shared/TabViewShared.cpp
        src/Systems/Shared/TabViewShared.h
        src/Systems/Input/CommandPaletteKeydown.cpp
        src/Systems/Input/CommandPaletteKeydown.h
        src/Systems/Input/SelectableMousePress.cpp
        src/Systems/Input/SelectableMousePress.h
        src/Systems/Input/TabViewKeydown.cpp
        src/Systems/Input/TabViewKeydown.h
        src/Systems/Groups/TabViewSystemGroup.h
        src/Systems/Input/TabViewClick.h
        src/Systems/Input/TabViewClick.cpp
        src/Systems/Groups/EditSystemGroup.h
        src/Systems/Shared/EditShared.cpp
        src/Systems/Shared/EditShared.h
        src/Systems/Rendering/CommandPaletteDraw.cpp
        src/Systems/Rendering/CommandPaletteDraw.h
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
