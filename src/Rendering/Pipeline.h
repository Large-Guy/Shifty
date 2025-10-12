#ifndef SHIFTY_PIPELINE_H
#define SHIFTY_PIPELINE_H
#include <memory>
#include <SDL3/SDL_gpu.h>

#include "Shader.h"


class Pipeline
{
public:
    SDL_GPUGraphicsPipeline* pipeline = nullptr;

    std::shared_ptr<Shader> vertex = nullptr;
    std::shared_ptr<Shader> fragment = nullptr;

    void load()
    {
    }
};


#endif //SHIFTY_PIPELINE_H
