#include "DrawSystem.h"

void DrawSystem::drawUIRect(ComRef<Draw> draw, const UIRectInfo& info)
{
    //Other
    auto vertShader = draw->loadShader("res/shaders/UIRect.hlsl", SDL_GPU_SHADERSTAGE_VERTEX, 0, 1, 0, 0);
    auto fragShader = draw->loadShader("res/shaders/UIRect.hlsl", SDL_GPU_SHADERSTAGE_FRAGMENT, 0, 1, 0, 0);

    SDL_GPURasterizerState rasterizer{};
    rasterizer.cull_mode = SDL_GPU_CULLMODE_NONE;
    rasterizer.fill_mode = SDL_GPU_FILLMODE_FILL;

    auto pipeline = draw->loadPipeline(vertShader, fragShader, rasterizer);

    SDL_BindGPUGraphicsPipeline(draw->currentPass, pipeline->pipeline);

    SDL_PushGPUVertexUniformData(draw->currentCmdBuf, 0, &info, sizeof(UIRectInfo));
    SDL_PushGPUFragmentUniformData(draw->currentCmdBuf, 0, &info, sizeof(UIRectInfo));

    SDL_DrawGPUPrimitives(draw->currentPass, 6, 1, 0, 0);
}
