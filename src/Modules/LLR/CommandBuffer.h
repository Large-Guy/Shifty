#ifndef SHIFTY_COMMANDBUFFER_H
#define SHIFTY_COMMANDBUFFER_H
#include "Pipeline.h"
#include "SDL3/SDL_gpu.h"


class CommandBuffer
{
    SDL_GPUDevice* device;
    SDL_GPUCommandBuffer* buffer;

public:
    CommandBuffer(SDL_GPUDevice* device);

    void usePipeline(Pipeline* pipeline);
    void pushVertexUniform(int index, void* data, size_t size);
    void pushFragmentUniform(int index, void* data, size_t size);

    void drawPrimitives(int vertices, int instances, int first, int firstInstance);
};


#endif //SHIFTY_COMMANDBUFFER_H
