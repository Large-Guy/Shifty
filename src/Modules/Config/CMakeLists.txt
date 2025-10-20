add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/config_generated.h
        COMMAND xxd -i ${CMAKE_SOURCE_DIR}/res/config.json > ${CMAKE_BINARY_DIR}/config_generated.h
        DEPENDS ${CMAKE_SOURCE_DIR}/res/config.json
        COMMENT "Generating config_generated.h from config.json"
)

add_custom_target(GenerateConfigHeader ALL
        DEPENDS ${CMAKE_BINARY_DIR}/config_generated.h
)

message(${CMAKE_BINARY_DIR}/config_generated.h)
message(${CMAKE_SOURCE_DIR}/res/config.json)

add_library(ShiftyConfig STATIC
        GlobalConfig.h
        GlobalConfig.cpp
        ${CMAKE_BINARY_DIR}/config_generated.h
)

target_link_libraries(ShiftyConfig PUBLIC
        Shifty::Dependencies
)

target_include_directories(ShiftyConfig PUBLIC
        ${CMAKE_SOURCE_DIR}/external/sj.h
        ${CMAKE_BINARY_DIR}
)

add_dependencies(ShiftyConfig GenerateConfigHeader)

add_library(Shifty::Config ALIAS ShiftyConfig)