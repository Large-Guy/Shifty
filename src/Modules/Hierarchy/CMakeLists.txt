add_library(ShiftyHierarchy STATIC
        Components/Hierarchy.h
        Systems/HierarchySystem.cpp
        Systems/HierarchySystem.h
)

target_link_libraries(ShiftyHierarchy PUBLIC
        Shifty::ECS
)

add_library(Shifty::Hierarchy ALIAS ShiftyHierarchy)