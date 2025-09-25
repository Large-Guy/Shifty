#ifndef SHIFTY_ARCHETYPE_H
#define SHIFTY_ARCHETYPE_H
#include <cstdint>

#include "Component.h"
#include "Type.h"

using ArchetypeID = uint32_t;
using EntityID = uint32_t;

struct Archetype {
    struct Column {
        void* elements = nullptr;
        size_t count = 0;
        size_t capacity = 1;
        Component component = {};

        std::vector<EntityID> owners = {};

        Column();

        Column(Component component);

        void* operator[](size_t index) const;

        void* add(EntityID owner);

        void* add(EntityID owner, void* instance);
    };

    struct Record {
        size_t column;
    };

    struct Edge {
        Archetype* add = nullptr;
        Archetype* remove = nullptr;

        Edge(Archetype* add, Archetype* remove);
    };

    using Map = std::unordered_map<Archetype*, Record>;

    static std::unordered_map<Type, Archetype*, TypeHash> archetypeIndex;
    static std::unordered_map<Component, Map, ComponentHash> componentIndex;

    Archetype(const Type& type);

    ArchetypeID id = 0;
    Type type = {};
    std::unordered_map<Component, Edge, ComponentHash> edges = {};
    std::vector<Column> components = {};

    Edge& getEdge(const Component& component);

    void remove(size_t row);

    size_t add(EntityID owner);

    static Archetype* getArchetype(const Type& type);
};


#endif //SHIFTY_ARCHETYPE_H
