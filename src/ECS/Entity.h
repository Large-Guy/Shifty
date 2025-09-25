#ifndef SHIFTY_ENTITY_H
#define SHIFTY_ENTITY_H

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>

#include "Component.h"
#include "Archetype.h"
#include "../EventBus.h"

using EntityID = uint32_t;

template<typename T>
struct OnComponentCreate {
    EntityID entity;
    T& component;
};

class Entity {
    struct Record {
        Archetype* archetype;
        size_t row;
    };

    static std::unordered_map<EntityID, Record> entityIndex;
    static EntityID count;

    void move(Archetype* current, size_t row, Archetype* next);

public:
    EntityID id;

    Entity(EntityID id = 0);

    static Entity create();

    bool has(Component component) const;

    void* get(Component component) const;

    void* add(Component component, void* instance = nullptr);

    void remove(Component component);

    template<typename T>
    bool has() const {
        return has(Component::get<T>());
    }

    template<typename T>
    T& get() const {
        return *static_cast<T*>(get(Component::get<T>()));
    }

    template<typename T>
    T& add() {
        T* component = static_cast<T*>(add(Component::get<T>()));
        OnComponentCreate<T> event{id, *component};
        EventBus::emit(event);
        return *component;
    }

    template<typename T>
    T& add(T instance) {
        T* component = static_cast<T*>(add(Component::get<T>(), &instance));
        OnComponentCreate<T> event{id, *component};
        EventBus::emit(event);
        return *component;
    }

    template<typename T>
    void remove() {
        remove(Component::get<T>());
    }

    template<typename T>
    static void each(std::function<void(T&)> callback) {
        Archetype::Map& map = Archetype::componentIndex[Component::get<T>()];
        for (auto& element: map) {
            auto& column = element.first->components[element.second.column];
            for (size_t i = 0; i < column.count; ++i) {
                callback(*static_cast<T*>(column[i]));
            }
        }
    }

    template<typename T>
    static void each(std::function<void(Entity entity, T&)> callback) {
        Archetype::Map& map = Archetype::componentIndex[Component::get<T>()];
        for (auto& element: map) {
            auto& column = element.first->components[element.second.column];
            for (size_t i = 0; i < column.count; ++i) {
                callback(Entity(column.owners[i]), *static_cast<T*>(column[i]));
            }
        }
    }

    template<typename T>
    static Entity find() {
        const Archetype::Map& map = Archetype::componentIndex[Component::get<T>()];
        return {map.begin()->first->components[map.begin()->second.column].owners[0]};
    }
};

#endif //SHIFTY_ENTITY_H
