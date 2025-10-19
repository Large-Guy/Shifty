add_library(ShiftyConfig STATIC
        GlobalConfig.h
        GlobalConfig.cpp
)

target_link_libraries(ShiftyConfig PUBLIC
        Shifty::Dependencies
)

target_include_directories(ShiftyConfig PUBLIC
        ${CMAKE_SOURCE_DIR}/external/sj.h
)

add_library(Shifty::Config ALIAS ShiftyConfig)