add_library(ShiftyTabs STATIC
        Components/Tab.h
        Components/TabviewState.h

        Systems/TabDraw.cpp
        Systems/TabDraw.h
        Systems/TabviewClick.cpp
        Systems/TabviewClick.h
        Systems/TabviewDraw.cpp
        Systems/TabviewDraw.h
        Systems/TabviewKeydown.cpp
        Systems/TabviewKeydown.h
        Systems/TabviewShared.cpp
        Systems/TabviewShared.h
        Systems/TabviewUpdate.cpp
        Systems/TabviewUpdate.h
        Prefab.cpp
        Prefab.h
)

target_link_libraries(ShiftyTabs PUBLIC
        Shifty::ECS
        Shifty::Hierarchy
        Shifty::Config
)

add_library(Shifty::Tabs ALIAS ShiftyTabs)