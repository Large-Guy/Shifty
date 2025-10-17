cmake_minimum_required(VERSION 4.0)
cmake_policy(SET CMP0074 NEW)
if (APPLE)
    project(Shifty LANGUAGES C CXX OBJCXX)
else ()
    project(Shifty LANGUAGES C CXX)
endif ()
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
        src/Systems/PanelAnimationUpdate.cpp
        src/Systems/PanelAnimationUpdate.h
        src/Components/Focus.h
        src/Prefabs.cpp
        src/Prefabs.h
        src/Components/Selectable.h
        src/Systems/Commands/TabCommand.cpp
        src/Systems/Commands/TabCommand.h
        src/Systems/TabviewUpdate.cpp
        src/Systems/TabviewUpdate.h
        src/Components/TabviewState.h
        src/Components/Tab.h
        src/Systems/Shared/TabviewShared.cpp
        src/Systems/Shared/TabviewShared.h
        src/Systems/Input/CommandPaletteKeydown.cpp
        src/Systems/Input/CommandPaletteKeydown.h
        src/Systems/Input/SelectableMousePress.cpp
        src/Systems/Input/SelectableMousePress.h
        src/Systems/Input/TabviewKeydown.cpp
        src/Systems/Input/TabviewKeydown.h
        src/Systems/Groups/TabViewSystemGroup.h
        src/Systems/Input/TabviewClick.h
        src/Systems/Input/TabviewClick.cpp
        src/Systems/Groups/EditSystemGroup.h
        src/Systems/Shared/EditShared.cpp
        src/Systems/Shared/EditShared.h
        src/Systems/Rendering/CommandPaletteDraw.cpp
        src/Systems/Rendering/CommandPaletteDraw.h
        src/Systems/Rendering/PanelDraw.cpp
        src/Systems/Rendering/PanelDraw.h
        src/Systems/Rendering/TabviewDraw.cpp
        src/Systems/Rendering/TabviewDraw.h
        src/Systems/FocusUpdate.cpp
        src/Systems/FocusUpdate.h
        src/Rendering/Window.cpp
        src/Rendering/Window.h
        src/Rendering/Shader.cpp
        src/Rendering/Shader.h
        src/Systems/DrawResize.cpp
        src/Systems/DrawResize.h
        src/Rendering/Pipeline.cpp
        src/Rendering/Pipeline.h
        src/Drawing.cpp
        src/Drawing.h
        src/Components/Motion.h
        src/Systems/MotionUpdate.cpp
        src/Systems/MotionUpdate.h
)

if (APPLE)
    set(PLATFORM_SOURCES
            src/Rendering/Mac/Compatibility.hpp
            src/Rendering/Mac/Compatibility.mm
    )
endif ()

file(GLOB_RECURSE PLUGIN_SOURCES "src/Plugins/**/*.cpp")
file(GLOB_RECURSE PLUGIN_HEADERS "src/Plugins/**/*.h")

add_executable(Shifty
        ${CORE_SOURCES}
        ${PLUGIN_SOURCES}
        ${PLUGIN_HEADERS}
        ${PLATFORM_SOURCES}
)

set(CMAKE_FRAMEWORK_PATH "${CMAKE_FRAMEWORK_PATH};~/Library/Frameworks") # Or /Library/Frameworks

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
find_package(SDL3_image REQUIRED SDL3_image-shared)
find_package(SDL3_ttf REQUIRED SDL3_ttf-shared)

if (APPLE)
    find_library(COCOA_FRAMEWORK Cocoa)
endif ()

target_link_libraries(Shifty PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_ttf::SDL3_ttf
        ${COCOA_FRAMEWORK}
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
