add_library(ShiftyLLR STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Shader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Shader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Pipeline.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Pipeline.h
)

target_link_libraries(ShiftyLLR PUBLIC
        Shifty::Dependencies
        Shifty::Config
)

add_library(Shifty::LLR ALIAS ShiftyLLR)