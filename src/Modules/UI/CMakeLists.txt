add_library(ShiftyUI STATIC
        Components/Animation.h
        Components/Edit.h
        Components/Focus.h
        Components/Layout.h
        Components/Selectable.h
        Components/Text.h
        Components/Transform.h
        Components/Motion.h

        Systems/AnimationUpdate.cpp
        Systems/AnimationUpdate.h
        Systems/EditShared.cpp
        Systems/EditShared.h
        Systems/FocusUpdate.cpp
        Systems/FocusUpdate.h
        Systems/MotionUpdate.cpp
        Systems/MotionUpdate.h
        Systems/RenderTransformsCompute.cpp
        Systems/RenderTransformsCompute.h
        Systems/SelectableMousePress.cpp
        Systems/SelectableMousePress.h
        Systems/TextDraw.cpp
        Systems/TextDraw.h
        Systems/TextEditSystems.cpp
        Systems/TextEditSystems.h

        Prefabs.cpp
        Prefabs.h
)

target_link_libraries(ShiftyUI PUBLIC
        Shifty::Dependencies
        Shifty::Platform
        Shifty::ECS
        Shifty::EventBus
        Shifty::Drawing
)

add_library(Shifty::UI ALIAS ShiftyUI)