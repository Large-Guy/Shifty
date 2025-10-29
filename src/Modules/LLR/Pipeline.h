#ifndef SHIFTY_PIPELINE_H
#define SHIFTY_PIPELINE_H
#include <iostream>
#include <memory>

#include "Device.h"
#include "Shader.h"
#include "RenderPass.h"

class Pipeline
{
public:
    static Pipeline* bound;
    SDL_GPUGraphicsPipeline* pipeline = nullptr;

    std::shared_ptr<Device> device = nullptr;

    std::shared_ptr<Shader> vertex = nullptr;
    std::shared_ptr<Shader> fragment = nullptr;

    Pipeline(std::shared_ptr<Device> device, TextureFormat format, SDL_GPURasterizerState state,
             std::shared_ptr<Shader> vertex,
             std::shared_ptr<Shader> fragment);
    ~Pipeline();

    void bind(std::shared_ptr<RenderPass> pass);

    void vertexUniformPtr(int index, void* info, size_t size);
    void fragmentUniformPtr(int index, void* info, size_t size);

    template <typename T>
    void vertexUniform(int index, const T& info)
    {
        static_assert(!std::is_trivial_v<T>, "Type is non trivial and is not safe to upload to GPU!");
        vertexUniformPtr(index, const_cast<void*>(static_cast<const void*>(&info)), sizeof(T));
    }

    template <typename T>
    void fragmentUniform(int index, const T& info)
    {
        static_assert(!std::is_trivial_v<T>, "Type is non trivial and is not safe to upload to GPU!");
        fragmentUniformPtr(index, const_cast<void*>(static_cast<const void*>(&info)), sizeof(T));
    }
};


#endif //SHIFTY_PIPELINE_H
