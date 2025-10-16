#include "Pipeline.h"

#include <utility>

Pipeline::Pipeline(SDL_GPUDevice* device, SDL_GPUTextureFormat format, SDL_GPURasterizerState state,
                   std::shared_ptr<Shader> vertex,
                   std::shared_ptr<Shader> fragment)
{
    this->vertex = std::move(vertex);
    this->fragment = std::move(fragment);

    SDL_GPUGraphicsPipelineCreateInfo pipeline_info;
    pipeline_info = {

        .vertex_shader = this->vertex->shader,
        .fragment_shader = this->fragment->shader,
        .primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
        .rasterizer_state = state,

        .target_info = {
            .color_target_descriptions = (SDL_GPUColorTargetDescription[]){
                {
                    .format = format,
                    .blend_state = {
                        .src_color_blendfactor = SDL_GPU_BLENDFACTOR_SRC_ALPHA,
                        .dst_color_blendfactor = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
                        .color_blend_op = SDL_GPU_BLENDOP_ADD,
                        .src_alpha_blendfactor = SDL_GPU_BLENDFACTOR_SRC_ALPHA,
                        .dst_alpha_blendfactor = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
                        .alpha_blend_op = SDL_GPU_BLENDOP_ADD,
                        .enable_blend = true,
                    }
                }
            },
            .num_color_targets = 1,
        },
    };

    this->pipeline = SDL_CreateGPUGraphicsPipeline(device, &pipeline_info);

    if (!this->pipeline)
        throw std::runtime_error("Failed to create pipeline: " + std::string(SDL_GetError()));
}
