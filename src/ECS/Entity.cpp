#include "Entity.h"

#include <stdexcept>
#include <utility>


std::unordered_map<EntityID, Entity::Record> Entity::entityIndex = {};
EntityID Entity::count = 0;
const Entity Entity::null = {0};

void Entity::move(Archetype* current, size_t row, Archetype* next)
{
    size_t newRow = next->add(id);
    auto remIter = entityIndex.find(id);
    for (auto& component : current->type)
    {
        auto contains = std::find(next->type.begin(), next->type.end(), component);
        if (contains == next->type.end())
        {
            continue;
        }
        auto& record = Archetype::componentIndex[component][current];
        auto& column = current->components[record.column];
        auto& nextRecord = Archetype::componentIndex[component][next];
        auto& nextColumn = next->components[nextRecord.column];

        column.component.move(nextColumn[newRow], column[row]);
    }
    current->remove(row);
    entityIndex.erase(remIter);
    entityIndex.insert({id, {next, newRow}});
}

Entity::Entity(EntityID id)
{
    this->id = id;
}

bool Entity::operator==(const Entity& other) const
{
    return this->id == other.id;
}

bool Entity::operator==(const EntityID other) const
{
    return this->id == other;
}

Entity Entity::create()
{
    EntityID id = ++count;
    auto* archetype = Archetype::getArchetype({});
    auto record = Record{archetype, 0};
    entityIndex.insert({id, record});
    return {id};
}

bool Entity::has(Component component) const
{
    if (!entityIndex.contains(id))
    {
        throw std::runtime_error("Entity does not exist!");
    }
    auto* archetype = entityIndex.at(id).archetype;
    auto& archetypeSet = Archetype::componentIndex[component];
    return archetypeSet.contains(archetype);
}

void* Entity::get(Component component) const
{
    auto& record = entityIndex.at(id);
    auto* archetype = record.archetype;

    auto& set = Archetype::componentIndex[component];
    if (!set.contains(archetype))
    {
        return nullptr;
    }

    auto& archRecord = set[archetype];
    return archetype->components[archRecord.column][record.row];
}

void* Entity::add(Component component, void* instance)
{
    auto& record = entityIndex.at(id);
    auto* archetype = record.archetype;

    auto* archetypeNext = archetype->getEdge(component).add;
    move(archetype, record.row, archetypeNext);

    if (instance == nullptr)
        return get(component);

    void* dest = get(component);
    component.copy(dest, instance);

    return dest;
}

void Entity::remove(Component component)
{
    auto& record = entityIndex.at(id);
    auto* archetype = record.archetype;

    auto* archetypeNext = archetype->getEdge(component).remove;
    move(archetype, record.row, archetypeNext);
}

void Entity::destroy()
{
    auto& record = entityIndex.at(id);
    auto* archetype = record.archetype;
    archetype->remove(record.row);
    entityIndex.erase(id);
    id = 0;
}
