#ifndef SHIFTY_ENTITY_H
#define SHIFTY_ENTITY_H

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>

namespace Shifty::ECS {

    using EntityID = uint32_t;
    using ComponentID = uint32_t;
    using ArchetypeID = uint32_t;
    using Type = std::vector<ComponentID>;

    struct TypeHash {
        std::size_t operator()(const Type& type) const {
            std::size_t seed = 0;
            for (auto& item: type) {
                seed ^= std::hash<unsigned int>{}(item) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };

    struct Archetype {
        struct Column {
            void* elements;
            size_t size;
            size_t count;

            void* operator[](size_t index) const;

            void add();
        };

        struct Record {
            size_t column;
        };

        struct Edge {
            Archetype* add = nullptr;
            Archetype* remove = nullptr;

            Edge(Archetype* add, Archetype* remove);
        };

        using Map = std::unordered_map<ArchetypeID, Record>;

        static std::unordered_map<Type, Archetype, TypeHash> archetypeIndex;
        static std::unordered_map<ComponentID, Map> componentIndex;

        Archetype(const Type& type);

        ArchetypeID id = 0;
        Type type = {};
        std::unordered_map<ComponentID, Edge> edges = {};
        std::vector<Column> components = {};

        Edge& getEdge(ComponentID component);

        void remove(size_t row);

        size_t add();

        static Archetype* getArchetype(const Type& type);
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

        bool has(ComponentID component) const;

        void* get(ComponentID component) const;

        void add(ComponentID component);
    };

} // ECS
// Shifty

#endif //SHIFTY_ENTITY_H
