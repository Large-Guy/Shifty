#ifndef SHIFTY_COMPONENT_H
#define SHIFTY_COMPONENT_H
#include <cstddef>
#include <cstdint>
#include <functional>
#include <string>

using ComponentID = size_t;

struct Component
{
    std::string name; //DEBUGING PURPOSES ONLY
    ComponentID id;
    size_t size;
    std::function<void(void*)> constructor;
    std::function<void(void*)> destructor;
    std::function<void(void*, void*)> copy;
    std::function<void(void*, void*)> move;
    std::function<void(uint32_t)> onAdd;
    std::function<void(uint32_t)> onRemove;

    bool operator==(const Component&) const;

    template <typename T>
    constexpr static Component get(); //Impl in Entity.h
};

struct ComponentHash
{
    std::size_t operator()(const Component& component) const
    {
        return std::hash<unsigned int>{}(component.id);
    }
};

#endif //SHIFTY_COMPONENT_H
