#ifndef SHIFTY_COMPONENT_H
#define SHIFTY_COMPONENT_H
#include <cstddef>
#include <cstdint>
#include <functional>
#include <string>

using ComponentID = uint32_t;

struct Component {
    std::string name; //DEBUGING PURPOSES ONLY
    ComponentID id = 0;
    size_t size = 0;
    std::function<void(void*)> constructor = nullptr;
    std::function<void(void*)> destructor = nullptr;
    std::function<void(void*, void*)> copy = nullptr;
    std::function<void(void*, void*)> move = nullptr;

    Component() = default;

    Component(ComponentID id, size_t size, std::function<void(void*)> constructor,
              std::function<void(void*)> destructor,
              std::function<void(void*, void*)> copy, std::function<void(void*, void*)> move);

    bool operator==(const Component&) const;

    template<typename T>
    static Component get() {
        auto comp = Component(
            typeid(T).hash_code(),
            sizeof(T),
            [](void* ptr) { new(ptr) T(); },
            [](void* ptr) { delete static_cast<T*>(ptr); },
            [](void* dst, void* src) { *static_cast<T*>(dst) = *static_cast<T*>(src); },
            [](void* dst, void* src) { *static_cast<T*>(dst) = std::move(*static_cast<T*>(src)); }
        );
        comp.name = typeid(T).name();
        return comp;
    }
};

struct ComponentHash {
    std::size_t operator()(const Component& component) const {
        return std::hash<unsigned int>{}(component.id);
    }
};

#endif //SHIFTY_COMPONENT_H
