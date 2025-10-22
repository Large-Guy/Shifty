#include "Shader.h"

#include <iostream>
#include <stdexcept>
#include <__filesystem/filesystem_error.h>

#include "SDL3_shadercross/SDL_shadercross.h"

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

    const char* entrypoint = nullptr;
    SDL_GPUShaderFormat backendFormat = SDL_GetGPUShaderFormats(device);
    SDL_GPUShaderFormat format = SDL_GPU_SHADERFORMAT_INVALID;


#ifdef __APPLE__

    if (backendFormat & SDL_GPU_SHADERFORMAT_MSL)
    {
        format = SDL_GPU_SHADERFORMAT_MSL;
        if (stage == SDL_GPU_SHADERSTAGE_VERTEX)
        {
            entrypoint = "_vertex";
        }
        if (stage == SDL_GPU_SHADERSTAGE_FRAGMENT)
        {
            entrypoint = "_fragment";
        }
    }
    else
    {
        throw std::runtime_error("Could not find GPU shader format");
    }


#else
    if (backendFormat & SDL_GPU_SHADERFORMAT_SPIRV)
    {
        format = SDL_GPU_SHADERFORMAT_SPIRV;
        if (stage == SDL_GPU_SHADERSTAGE_VERTEX)
        {
            entrypoint = "_vertex";
        }
        if (stage == SDL_GPU_SHADERSTAGE_FRAGMENT)
        {
            entrypoint = "_fragment";
        }
    }
    else
    {
        throw std::runtime_error("Could not find GPU shader format");
    }
#endif

    if (entrypoint == nullptr)
    {
        throw std::runtime_error("Could not find GPU shader entry point");
    }

    size_t codeSize;
    void* code = SDL_LoadFile(path.c_str(), &codeSize);

    if (path.ends_with(".hlsl"))
    {
        std::filesystem::path filePath(path);
        std::filesystem::path shaderPath = filePath.parent_path();
        std::string parentPath = shaderPath.string();
        SDL_ShaderCross_HLSL_Info info = {
            .source = static_cast<const char*>(code),
            .entrypoint = entrypoint,
            .include_dir = parentPath.c_str(),
            .defines = nullptr,
            .shader_stage = stage == SDL_GPU_SHADERSTAGE_VERTEX
                                ? SDL_SHADERCROSS_SHADERSTAGE_VERTEX
                                : SDL_SHADERCROSS_SHADERSTAGE_FRAGMENT,
            .props = 0,
        };
        code = SDL_ShaderCross_CompileSPIRVFromHLSL(&info, &codeSize);
    }

    if (!code)
    {
        throw std::runtime_error("Failed to load shader: " + std::string(SDL_GetError()));
    }


#ifdef __APPLE__
    SDL_ShaderCross_SPIRV_Info transpileInfo = {
        .bytecode = static_cast<const Uint8*>(code),
        .bytecode_size = codeSize,
        .entrypoint = entrypoint,
        .shader_stage = stage == SDL_GPU_SHADERSTAGE_VERTEX
                            ? SDL_SHADERCROSS_SHADERSTAGE_VERTEX
                            : SDL_SHADERCROSS_SHADERSTAGE_FRAGMENT,
        .props = 0
    };

    void* transpiledCode = SDL_ShaderCross_TranspileMSLFromSPIRV(&transpileInfo);

    code = transpiledCode;

    if (code == nullptr)
    {
        throw std::runtime_error("Failed to transpile shader: " + std::string(SDL_GetError()));
    }

    std::cout << static_cast<const char*>(transpiledCode) << std::endl;

    codeSize = SDL_strlen(static_cast<const char*>(code));
#endif


    SDL_GPUShaderCreateInfo shaderInfo = {
        .code_size = codeSize,
        .code = static_cast<const uint8_t*>(code),
        .entrypoint = entrypoint,
        .format = format,
        .stage = stage,
        .num_samplers = samplers,
        .num_storage_textures = textures,
        .num_storage_buffers = storage,
        .num_uniform_buffers = uniforms,
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
