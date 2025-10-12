#include "Shader.h"

#include <stdexcept>

Shader::Shader()
= default;

Shader::~Shader()
{
}

void Shader::load(const std::string& path)
{
    const char* entrypoint;
    SDL_GPUShaderFormat backendFormat = SDL_GetGPUShaderFormats(device);
    SDL_GPUShaderFormat format = SDL_GPU_SHADERFORMAT_INVALID;
#ifdef __APPLE__
    if (backendFormat & SDL_GPU_SHADERFORMAT_MSL)
    {
        format = SDL_GPU_SHADERFORMAT_MSL;
        entrypoint = "main";
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

