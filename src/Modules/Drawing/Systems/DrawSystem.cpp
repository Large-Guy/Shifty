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

    pipeline->bind(draw->drawPass);

    pipeline->vertexUniform(0, info);
    pipeline->fragmentUniform(0, info);

    SDL_DrawGPUPrimitives(draw->drawPass->getPass(), 6, 1, 0, 0);
}
