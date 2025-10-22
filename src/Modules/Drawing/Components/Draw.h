#ifndef SHIFTY_DRAW_H
#define SHIFTY_DRAW_H

#include <cstring>
#include <memory>
#include <queue>
#include <vector>

#include "ECS/Entity.h"
#include "LLR/Pipeline.h"
#include "LLR/Shader.h"
#include "SDL3/SDL_render.h"

struct Draw
{
    struct Command
    {
        int priority = 0;

        virtual void execute(SDL_Renderer* renderer) = 0;

        Command(int priority)
        {
            this->priority = priority;
        }

        virtual ~Command() = default;
    };

    std::vector<std::shared_ptr<Command>> commands;
    SDL_Renderer* renderer;

    SDL_GPUDevice* gpuDevice;
    SDL_GPUTexture* renderTexture;
    SDL_GPUTextureFormat format;

    SDL_GPUCommandBuffer* currentCmdBuf;
    SDL_GPURenderPass* currentPass;

    SDL_GPUTransferBuffer* dataTransferBuffer;
    SDL_Texture* outputTexture;

    struct ShaderRegistry
    {
        std::string name;
        SDL_GPUShaderStage format;

        bool operator==(const ShaderRegistry& other) const
        {
            return name == other.name && format == other.format;
        }
    };

    struct ShaderRegistryHash
    {
        size_t operator()(const ShaderRegistry& shaderRegistry) const
        {
            return std::hash<std::string>()(shaderRegistry.name) ^ shaderRegistry.format;
        }
    };

    std::unordered_map<ShaderRegistry, std::shared_ptr<Shader>, ShaderRegistryHash> shaders;

    struct PipelineInfo
    {
        std::shared_ptr<Shader> vert;
        std::shared_ptr<Shader> frag;
        SDL_GPURasterizerState rasterState;

        bool operator==(const PipelineInfo& other) const
        {
            return vert.get() == other.vert.get() &&
                frag.get() == other.frag.get() &&
                std::memcmp(&rasterState, &other.rasterState, sizeof(SDL_GPURasterizerState)) == 0;
        }
    };

    struct PipelineHash
    {
        size_t operator()(const PipelineInfo& info) const
        {
            size_t h = 0;
            std::hash<void*> ptr_hash;
            std::hash<int> int_hash;

            h ^= ptr_hash(info.vert.get()) + 0x9e3779b9 + (h << 6) + (h >> 2);
            h ^= ptr_hash(info.frag.get()) + 0x9e3779b9 + (h << 6) + (h >> 2);

            // Combine all relevant rasterState fields
            h ^= int_hash(info.rasterState.cull_mode) + 0x9e3779b9 + (h << 6) + (h >> 2);
            h ^= int_hash(info.rasterState.depth_bias_clamp) + 0x9e3779b9 + (h << 6) + (h >> 2);
            h ^= int_hash(info.rasterState.depth_bias_constant_factor) + 0x9e3779b9 + (h << 6) + (h >> 2);
            h ^= int_hash(info.rasterState.depth_bias_slope_factor) + 0x9e3779b9 + (h << 6) + (h >> 2);
            h ^= int_hash(info.rasterState.enable_depth_bias) + 0x9e3779b9 + (h << 6) + (h >> 2);
            h ^= int_hash(info.rasterState.enable_depth_clip) + 0x9e3779b9 + (h << 6) + (h >> 2);
            h ^= int_hash(info.rasterState.fill_mode) + 0x9e3779b9 + (h << 6) + (h >> 2);
            h ^= int_hash(info.rasterState.front_face) + 0x9e3779b9 + (h << 6) + (h >> 2);
            h ^= int_hash(info.rasterState.padding1) + 0x9e3779b9 + (h << 6) + (h >> 2);
            h ^= int_hash(info.rasterState.padding2) + 0x9e3779b9 + (h << 6) + (h >> 2);

            return h;
        }
    };

    std::unordered_map<PipelineInfo, std::shared_ptr<Pipeline>, PipelineHash> pipelines;

    int width, height;

    void pushCommand(const std::shared_ptr<Command>& command)
    {
        auto iter = commands.begin();
        for (; iter != commands.end(); ++iter)
        {
            if (command->priority < (*iter)->priority)
            {
                break;
            }
        }
        commands.insert(iter, command);
    }

    std::shared_ptr<Shader> loadShader(const std::string& path, SDL_GPUShaderStage stage, int samplers, int ubos,
                                       int ssbos,
                                       int textures)
    {
        if (shaders.contains({path, stage}))
        {
            return shaders[{path, stage}];
        }

        std::shared_ptr<Shader> newShader = std::make_shared<Shader>(gpuDevice, path, stage, samplers, ubos, ssbos,
                                                                     textures);
        shaders[{path, stage}] = newShader;
        return newShader;
    }

    std::shared_ptr<Pipeline> loadPipeline(std::shared_ptr<Shader> vertex,
                                           std::shared_ptr<Shader> fragment,
                                           SDL_GPURasterizerState state)
    {
        auto pipeline = PipelineInfo{
            vertex,
            fragment,
            state
        };
        if (pipelines.contains(pipeline))
        {
            return pipelines[pipeline];
        }

        std::shared_ptr<Pipeline> newPipeline = std::make_shared<Pipeline>(gpuDevice, format, state, vertex, fragment);

        pipelines[pipeline] = newPipeline;
        return newPipeline;
    }
};

struct OnDraw
{
    ComRef<Draw> draw;
};

#endif //SHIFTY_DRAW_H
