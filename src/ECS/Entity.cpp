#include "Entity.h"

#include <stdexcept>
#include <utility>


std::unordered_map<Type, Archetype *, TypeHash> Archetype::archetypeIndex = {};
std::unordered_map<Component, Archetype::Map, ComponentHash> Archetype::componentIndex = {};

std::unordered_map<EntityID, Entity::Record> Entity::entityIndex = {};
EntityID Entity::count = 0;

Component::Component(ComponentID id, size_t size, std::function<void(void *)> constructor,
                     std::function<void(void *)> destructor,
                     std::function<void(void *, void *)> copy, std::function<void(void *, void *)> move) {
    this->id = id;
    this->size = size;
    this->constructor = std::move(constructor);
    this->destructor = std::move(destructor);
    this->copy = std::move(copy);
    this->move = std::move(move);
}

bool Component::operator==(const Component &other) const {
    return this->id == other.id;
}

Archetype::Column::Column(Component component) {
    this->component = std::move(component);
    this->elements = nullptr;
    this->count = 0;
    this->capacity = 0;
}


void *Archetype::Column::operator[](size_t index) const {
    return (static_cast<char *>(elements) + component.size * index);
}

void *Archetype::Column::add(EntityID owner) {
    count++;
    if (count > capacity) {
        if (capacity == 0)
            capacity = 1;
        capacity *= 2;
        if (elements == nullptr)
            elements = malloc(capacity * component.size);
        else
            elements = realloc(elements, capacity * component.size);
    }
    void *root = static_cast<char *>(elements) + (component.size * count - component.size);
    component.constructor(root);
    owners.push_back(owner);
    return root;
}

void *Archetype::Column::add(EntityID owner, void *instance) {
    void *dest = add(owner);
    component.copy(dest, instance);
    return dest;
}

Archetype::Edge::Edge(Archetype *add, Archetype *remove) : add(add),
                                                           remove(remove) {
}

Archetype::Archetype(const Type &type) {
    if (archetypeIndex.contains(type)) {
        throw std::runtime_error("Cannot create two archetypes of the same type!");
    }
    this->id = archetypeIndex.size();
    this->type = type;
    for (int i = 0; i < type.size(); ++i) {
        components.emplace_back(type[i]);
        componentIndex[type[i]][this].column = i;
    }
    archetypeIndex.insert({this->type, this});
}

Archetype::Edge &Archetype::getEdge(const Component &component) {
    if (edges.contains(component)) {
        return edges.at(component);
    }
    Archetype *add = nullptr;
    Archetype *remove = nullptr;
    Type addType = type;
    addType.push_back(component);

    add = archetypeIndex.insert({addType, new Archetype{addType}}).first->second;

    Type removeType = type;
    auto item = std::find(removeType.begin(), removeType.end(), component);
    if (item != removeType.end()) {
        removeType.erase(item);

        remove = archetypeIndex.insert({removeType, new Archetype{removeType}}).first->second;
    }
    return edges.insert({component, {add, remove}}).first->second;
}

void Archetype::remove(size_t row) {
    //This will eventually mark the row as unused and then the next component to be added with fill in that row
}

size_t Archetype::add(EntityID owner) {
    for (auto &column: components) {
        column.add(owner);
    }
    size_t row = 0;
    if (!components.empty())
        row = components[0].count - 1;
    return row;
}

Archetype *Archetype::getArchetype(const Type &type) {
    if (archetypeIndex.contains(type)) {
        return archetypeIndex.at(type);
    }


    archetypeIndex.insert({type, new Archetype{type}});
    return archetypeIndex.at(type);
}

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

void Entity::add(Component component, void *instance) {
    auto &record = entityIndex.at(id);
    auto *archetype = record.archetype;

    auto *archetypeNext = archetype->getEdge(component).add;
    move(archetype, record.row, archetypeNext);
}
