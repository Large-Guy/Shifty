#ifndef SHIFTY_ENTITY_H
#define SHIFTY_ENTITY_H

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <iostream>
#include <ostream>

#include "../EventBus.h"

using ComponentID = uint32_t;

struct Component {
    ComponentID id = 0;
    size_t size = 0;
    std::function<void(void *)> constructor = nullptr;
    std::function<void(void *)> destructor = nullptr;
    std::function<void(void *, void *)> copy = nullptr;
    std::function<void(void *, void *)> move = nullptr;

    Component() = default;

    Component(ComponentID id, size_t size, std::function<void(void *)> constructor,
              std::function<void(void *)> destructor,
              std::function<void(void *, void *)> copy, std::function<void(void *, void *)> move);

    bool operator==(const Component &) const;

    template<typename T>
    static Component get() {
        return Component(
            typeid(T).hash_code(),
            sizeof(T),
            [](void *ptr) { new(ptr) T(); },
            [](void *ptr) { delete static_cast<T *>(ptr); },
            [](void *dst, void *src) { *static_cast<T *>(dst) = *static_cast<T *>(src); },
            [](void *dst, void *src) { *static_cast<T *>(dst) = std::move(*static_cast<T *>(src)); }
        );
    }
};

struct ComponentHash {
    std::size_t operator()(const Component &component) const {
        return std::hash<unsigned int>{}(component.id);
    }
};

using EntityID = uint32_t;
using ArchetypeID = uint32_t;
using Type = std::vector<Component>;

struct TypeHash {
    std::size_t operator()(const Type &type) const {
        std::size_t seed = 0;

        for (auto &item: type) {
            ComponentHash componentHash = {};
            seed ^= std::hash<unsigned int>{}(componentHash(item)) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

struct Archetype {
    struct Column {
        void *elements = nullptr;
        size_t count = 0;
        size_t capacity = 1;
        Component component = {};

        std::vector<EntityID> owners = {};

        Column(Component component);

        void *operator[](size_t index) const;

        void *add(EntityID owner);

        void *add(EntityID owner, void *instance);
    };

    struct Record {
        size_t column;
    };

    struct Edge {
        Archetype *add = nullptr;
        Archetype *remove = nullptr;

        Edge(Archetype *add, Archetype *remove);
    };

    using Map = std::unordered_map<Archetype *, Record>;

    static std::unordered_map<Type, Archetype *, TypeHash> archetypeIndex;
    static std::unordered_map<Component, Map, ComponentHash> componentIndex;

    Archetype(const Type &type);

    ArchetypeID id = 0;
    Type type = {};
    std::unordered_map<Component, Edge, ComponentHash> edges = {};
    std::vector<Column> components = {};

    Edge &getEdge(const Component &component);

    void remove(size_t row);

    size_t add(EntityID owner);

    static Archetype *getArchetype(const Type &type);
};

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

///@class System
///This encourages systems to do ONE THING ONLY keeping code more modular.
///Only ONE event should be subscribed to per system.
template<typename T>
class System {
public:
    virtual void process(const T &) {
    }

    System() {
        EventBus::subscribe<T>([this](T event) {
            this->process(event);
        });
    }

    virtual ~System() {
    }
};

#endif //SHIFTY_ENTITY_H
