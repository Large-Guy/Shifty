#include "CommandBuffer.h"

CommandBuffer::CommandBuffer(SDL_GPUDevice* device)
{
    this->device = device;
    this->buffer = SDL_AcquireGPUCommandBuffer(device);
}

void CommandBuffer::usePipeline(Pipeline* pipeline)
{
}

void CommandBuffer::pushVertexUniform(int index, void* data, size_t size)
{
}

void CommandBuffer::pushFragmentUniform(int index, void* data, size_t size)
{
}

void CommandBuffer::drawPrimitives(int vertices, int instances, int first, int firstInstance)
{
}

