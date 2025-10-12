#ifndef SHIFTY_DRAW_H
#define SHIFTY_DRAW_H

#include <memory>
#include <queue>
#include <vector>
#include <SDL3/SDL.h>

#include "ECS/Entity.h"
#include "Rendering/Shader.h"

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

    SDL_GPUTransferBuffer* dataTransferBuffer;
    SDL_Texture* outputTexture;

    std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;

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

    std::shared_ptr<Shader> load(const std::string& path, SDL_GPUShaderStage stage, int samplers, int ubos, int ssbos,
                                 int textures)
    {
        if (shaders.contains(path))
        {
            return shaders[path];
        }

        std::shared_ptr<Shader> newShader = std::make_shared<Shader>();
        newShader->device = gpuDevice;
        newShader->samplers = samplers;
        newShader->uniforms = ubos;
        newShader->storage = ssbos;
        newShader->textures = textures;
        newShader->stage = stage;
        newShader->load(path);

        shaders[path] = newShader;
        return newShader;
    }
};

struct OnDraw
{
    ComRef<Draw> draw;
};

#endif //SHIFTY_DRAW_H
