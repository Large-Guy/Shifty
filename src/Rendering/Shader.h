#ifndef SHIFTY_SHADER_H
#define SHIFTY_SHADER_H
#include <string>
#include <SDL3/SDL_gpu.h>


class Shader
{
public:
    SDL_GPUShader* shader = nullptr;

    SDL_GPUDevice* device = nullptr;
    std::string path;
    SDL_GPUShaderStage stage = SDL_GPU_SHADERSTAGE_VERTEX;
    uint32_t samplers = 0;
    uint32_t uniforms = 0;
    uint32_t storage = 0;
    uint32_t textures = 0;

    Shader(SDL_GPUDevice* device, const std::string& path, SDL_GPUShaderStage stage, uint32_t samplers,
           uint32_t uniforms, uint32_t storage, uint32_t textures);
    ~Shader();
};


#endif //SHIFTY_SHADER_H
