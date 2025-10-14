#include "Shader.h"

#include <stdexcept>

Shader::Shader(SDL_GPUDevice* device, const std::string& path, SDL_GPUShaderStage stage, uint32_t samplers,
               uint32_t uniforms, uint32_t storage, uint32_t textures)
{
    this->device = device;
    this->path = path;
    this->stage = stage;
    this->samplers = samplers;
    this->uniforms = uniforms;
    this->storage = storage;
    this->textures = textures;

    const char* entrypoint;
    SDL_GPUShaderFormat backendFormat = SDL_GetGPUShaderFormats(device);
    SDL_GPUShaderFormat format = SDL_GPU_SHADERFORMAT_INVALID;
#ifdef __APPLE__
    if (backendFormat & SDL_GPU_SHADERFORMAT_MSL)
    {
        format = SDL_GPU_SHADERFORMAT_MSL;
        if (stage == SDL_GPU_SHADERSTAGE_VERTEX)
            entrypoint = "main_vertex";
        else if (stage == SDL_GPU_SHADERSTAGE_FRAGMENT)
            entrypoint = "main_fragment";
    }
    else
    {
        throw std::runtime_error("Could not find GPU shader format");
    }
#else
    if (backendFormat & SDL_GPU_SHADERFORMAT_SPIRV)
    {
        format = SDL_GPU_SHADERFORMAT_SPIRV;
        entrypoint = "main";
    }
    else
    {
        throw std::runtime_error("Could not find GPU shader format");
    }
#endif

    size_t codeSize;
    void* code = SDL_LoadFile(path.c_str(), &codeSize);

    if (!code)
    {
        throw std::runtime_error("Failed to load shader: " + std::string(SDL_GetError()));
    }

    SDL_GPUShaderCreateInfo shaderInfo = {
        .code = static_cast<const uint8_t*>(code),
        .code_size = codeSize,
        .entrypoint = entrypoint,
        .format = format,
        .stage = stage,
        .num_samplers = samplers,
        .num_uniform_buffers = uniforms,
        .num_storage_buffers = storage,
        .num_storage_textures = textures,
    };

    shader = SDL_CreateGPUShader(device, &shaderInfo);

    if (!shader)
    {
        throw std::runtime_error("Failed to create shader: " + std::string(SDL_GetError()));
    }

    SDL_free(code);
}

Shader::~Shader()
{
}
