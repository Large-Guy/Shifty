#ifndef SHIFTY_ENTITY_H
#define SHIFTY_ENTITY_H

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>

#include "Component.h"
#include "Archetype.h"

using EntityID = uint32_t;


class Entity {
    struct Record {
        Archetype *archetype;
        size_t row;
    };

    static std::unordered_map<EntityID, Record> entityIndex;
    static EntityID count;

    void move(Archetype *current, size_t row, Archetype *next);

public:
    EntityID id;

    Entity(EntityID id = 0);

    static Entity create();

    bool has(Component component) const;

    void *get(Component component) const;

    void add(Component component, void *instance = nullptr);

    template<typename T>
    bool has() const {
        return has(Component::get<T>());
    }

    template<typename T>
    T &get() const {
        return *static_cast<T *>(get(Component::get<T>()));
    }

    template<typename T>
    void add() {
        add(Component::get<T>());
    }

    template<typename T>
    void add(T component) {
        add(Component::get<T>(), &component);
    }

    template<typename T>
    static void each(std::function<void(T &)> callback) {
        Archetype::Map &map = Archetype::componentIndex[Component::get<T>()];
        for (auto &element: map) {
            auto &column = element.first->components[element.second.column];
            for (size_t i = 0; i < column.count; ++i) {
                callback(*static_cast<T *>(column[i]));
            }
        }
    }

    template<typename T>
    static void each(std::function<void(Entity entity, T &)> callback) {
        Archetype::Map &map = Archetype::componentIndex[Component::get<T>()];
        for (auto &element: map) {
            auto &column = element.first->components[element.second.column];
            for (size_t i = 0; i < column.count; ++i) {
                callback(Entity(column.owners[i]), *static_cast<T *>(column[i]));
            }
        }
    }

    template<typename T>
    static Entity find() {
        const Archetype::Map &map = Archetype::componentIndex[Component::get<T>()];
        return {map.begin()->first->components[map.begin()->second.column].owners[0]};
    }
};

#endif //SHIFTY_ENTITY_H
