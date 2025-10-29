add_library(ShiftyLLR STATIC
        Shader.cpp
        Shader.h
        Pipeline.cpp
        Pipeline.h
        CommandBuffer.cpp
        CommandBuffer.h
        RenderPass.cpp
        RenderPass.h
        Device.cpp
        Device.h
        Texture.cpp
        Texture.h
        Color.cpp
        Color.h
        Viewport.cpp
        Viewport.h
        Download.cpp
        Download.h
        TransferBuffer.cpp
        TransferBuffer.h
)

target_link_libraries(ShiftyLLR PUBLIC
        Shifty::Dependencies
        Shifty::Config
)

add_library(Shifty::LLR ALIAS ShiftyLLR)