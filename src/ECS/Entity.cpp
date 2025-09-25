#include "Entity.h"

#include <stdexcept>
#include <utility>


std::unordered_map<EntityID, Entity::Record> Entity::entityIndex = {};
EntityID Entity::count = 0;

void Entity::move(Archetype *current, size_t row, Archetype *next) {
    size_t newRow = next->add(id);
    auto remIter = entityIndex.find(id);
    for (auto &component: current->type) {
        auto &record = Archetype::componentIndex[component][current];
        auto &column = current->components[record.column];
        auto &nextRecord = Archetype::componentIndex[component][next];
        auto &nextColumn = next->components[nextRecord.column];

        column.component.move(nextColumn[row], column[newRow]);
    }
    current->remove(row);
    entityIndex.erase(remIter);
    entityIndex.insert({id, {next, newRow}});
}

Entity::Entity(EntityID id) {
    this->id = id;
}

Entity Entity::create() {
    EntityID id = ++count;
    auto *archetype = Archetype::getArchetype({});
    auto record = Record{archetype, 0};
    entityIndex.insert({id, record});
    return {id};
}

bool Entity::has(Component component) const {
    if (!entityIndex.contains(id)) {
        throw std::runtime_error("Entity does not exist!");
    }
    auto *archetype = entityIndex.at(id).archetype;
    auto &archetypeSet = Archetype::componentIndex[component];
    return archetypeSet.contains(archetype);
}

void *Entity::get(Component component) const {
    auto &record = entityIndex.at(id);
    auto *archetype = record.archetype;

    auto &set = Archetype::componentIndex[component];
    if (!set.contains(archetype)) {
        return nullptr;
    }

    auto &archRecord = set[archetype];
    return archetype->components[archRecord.column][record.row];
}

void *Entity::add(Component component, void *instance) {
    auto &record = entityIndex.at(id);
    auto *archetype = record.archetype;

    auto *archetypeNext = archetype->getEdge(component).add;
    move(archetype, record.row, archetypeNext);

    if (instance == nullptr)
        return get(component);

    void *dest = get(component);
    component.copy(dest, instance);

    return dest;
}
