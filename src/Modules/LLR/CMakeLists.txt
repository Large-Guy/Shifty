if (APPLE)
    set(COMPATIBILITY_SOURCES
            Mac/Compatibility.mm
            Mac/Compatibility.hpp
    )
endif ()

add_library(ShiftyLLR STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Shader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Shader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Pipeline.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Pipeline.h

        ${COMPATIBILITY_SOURCES}
)

target_link_libraries(ShiftyLLR PUBLIC
        Shifty::Dependencies
)

add_library(Shifty::LLR ALIAS ShiftyLLR)