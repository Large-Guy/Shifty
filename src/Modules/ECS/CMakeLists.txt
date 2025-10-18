add_library(ShiftyECS STATIC
        Archetype.cpp
        Archetype.h
        Component.cpp
        Component.h
        Entity.cpp
        Entity.h
        System.cpp
        System.h
        Type.cpp
        Type.h
)

add_library(Shifty::ECS ALIAS ShiftyECS)