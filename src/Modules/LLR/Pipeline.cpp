#include "Pipeline.h"

#include <utility>

#include "RenderPass.h"

Pipeline* Pipeline::bound = nullptr;

Pipeline::Pipeline(std::shared_ptr<Device> device, TextureFormat format, SDL_GPURasterizerState state,
                   std::shared_ptr<Shader> vertex,
                   std::shared_ptr<Shader> fragment)
{
    this->device = device;

    this->vertex = std::move(vertex);
    this->fragment = std::move(fragment);

    SDL_GPUTextureFormat form;
    switch (format)
    {
    case TextureFormat::R8G8B8A8_SRGB:
        form = SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM;
        break;
    }

    SDL_GPUGraphicsPipelineCreateInfo pipeline_info;
    pipeline_info = {

        .vertex_shader = this->vertex->shader,
        .fragment_shader = this->fragment->shader,
        .primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
        .rasterizer_state = state,

        .target_info = {
            .color_target_descriptions = (SDL_GPUColorTargetDescription[]){
                {
                    .format = form,
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

    this->pipeline = SDL_CreateGPUGraphicsPipeline(device->device, &pipeline_info);

    if (!this->pipeline)
        throw std::runtime_error("Failed to create pipeline: " + std::string(SDL_GetError()));
}

Pipeline::~Pipeline()
{
    if (pipeline)
    {
        SDL_ReleaseGPUGraphicsPipeline(device->device, pipeline);
        pipeline = nullptr;
    }
}

void Pipeline::bind(std::shared_ptr<RenderPass> pass)
{
    SDL_BindGPUGraphicsPipeline(pass->pass, pipeline);
}

void Pipeline::vertexUniformPtr(int index, void* info, size_t size)
{
    SDL_PushGPUVertexUniformData(device->getCommandBuffer(), index, info, size);
}

void Pipeline::fragmentUniformPtr(int index, void* info, size_t size)
{
    SDL_PushGPUFragmentUniformData(device->getCommandBuffer(), index, info, size);
}
