#include "Entity.h"


namespace Shifty::ECS {
    std::unordered_map<Type, Archetype, TypeHash> Archetype::archetypeIndex = {};
    std::unordered_map<ComponentID, Archetype::Map> Archetype::componentIndex = {};

    std::unordered_map<EntityID, Entity::Record> Entity::entityIndex = {};
    EntityID Entity::count = 0;

    void* Archetype::Column::operator[](size_t index) const {
        return (void*) ((char*) elements + (size * index));
    }

    void Archetype::Column::add() {

    }

    Archetype::Edge::Edge(Archetype* add, Archetype* remove) : add(add),
                                                               remove(remove) {
    }

    Archetype::Archetype(const Type& type) {
        if (archetypeIndex.contains(type)) {
            throw std::runtime_error("Cannot create two archetypes of the same type!");
        }
        this->id = archetypeIndex.size();
        this->type = type;
        for (int i = 0; i < type.size(); ++i) {
            components.push_back({});
            componentIndex[type[i]][id].column = i;
        }
    }

    Archetype::Edge& Archetype::getEdge(ComponentID component) {
        if (edges.contains(component)) {
            return edges.at(component);
        } else {
            Archetype* add = nullptr;
            Archetype* remove = nullptr;
            Type addType = type;
            addType.push_back(component);

            add = &archetypeIndex.insert({addType, {addType}}).first->second;

            Type removeType = type;
            auto item = std::find(removeType.begin(), removeType.end(), component);
            if (item != removeType.end()) {
                removeType.erase(item);

                remove = &archetypeIndex.insert({removeType, {removeType}}).first->second;
            }
            return edges.insert({component, {add, remove}}).first->second;
        }
    }

    void Archetype::remove(size_t row) {
        //This will eventually mark the row as unused and then the next component to be added with fill in that row
    }

    size_t Archetype::add() {
        for (auto& column: components) {
            column.add();
        }
        size_t row = 0;
        if (!components.empty())
            row = components[0].count;
        return row;
    }

    Archetype* Archetype::getArchetype(const Type& type) {
        if (archetypeIndex.contains(type)) {
            return &archetypeIndex.at(type);
        }


        archetypeIndex.insert({type, {type}});
        return &archetypeIndex.at(type);
    }

    void Entity::move(Archetype* current, size_t row, Archetype* next) {
        current->remove(row);
        size_t newRow = next->add();
        auto remIter = entityIndex.find(id);
        entityIndex.erase(remIter);
        entityIndex.insert({id, {next, newRow}});
    }

    Entity::Entity(EntityID id) {
        this->id = id;
    }

    Entity Entity::create() {
        EntityID id = ++count;
        auto* archetype = Archetype::getArchetype({});
        auto record = Record{archetype, 0};
        entityIndex.insert({id, record});
        return {id};
    }

    bool Entity::has(ComponentID component) const {
        if (!entityIndex.contains(id)) {
            throw std::runtime_error("Entity does not exist!");
        }
        auto* archetype = entityIndex.at(id).archetype;
        auto& archetypeSet = Archetype::componentIndex[component];
        return archetypeSet.contains(archetype->id);
    }

    void* Entity::get(ComponentID component) const {
        auto& record = entityIndex.at(id);
        auto* archetype = record.archetype;

        auto& set = Archetype::componentIndex[component];
        if (!set.contains(archetype->id)) {
            return nullptr;
        }

        auto& archRecord = set[archetype->id];
        return archetype->components[archRecord.column][record.row];
    }

    void Entity::add(Shifty::ECS::ComponentID component) {
        auto& record = entityIndex.at(id);
        auto* archetype = record.archetype;

        auto archetypeNext = archetype->getEdge(component).add;
        move(archetype, record.row, archetypeNext);
    }
} // ECS
// Shifty