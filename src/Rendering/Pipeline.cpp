#include "Pipeline.h"

#include <utility>

Pipeline::Pipeline(SDL_GPUDevice* device, SDL_GPUTextureFormat format, SDL_GPURasterizerState state,
                   std::shared_ptr<Shader> vertex,
                   std::shared_ptr<Shader> fragment)
{
    this->vertex = std::move(vertex);
    this->fragment = std::move(fragment);

    SDL_GPUGraphicsPipelineCreateInfo pipeline_info = {
        .target_info = {
            .num_color_targets = 1,
            .color_target_descriptions = (SDL_GPUColorTargetDescription[]){
                {
                    .format = format
                }
            },
        },
        .primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
        .vertex_shader = this->vertex->shader,
        .fragment_shader = this->fragment->shader,
        .rasterizer_state = state
    };

    this->pipeline = SDL_CreateGPUGraphicsPipeline(device, &pipeline_info);
}
