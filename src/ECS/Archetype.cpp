#include "Archetype.h"

#include <cstring>
#include <iostream>
#include <stdexcept>

std::unordered_map<Type, Archetype*, TypeHash> Archetype::archetypeIndex = {};
std::unordered_map<Component, Archetype::Map, ComponentHash> Archetype::componentIndex = {};

Archetype::Column::Column()
{
    throw std::runtime_error("Columns shouldn't be created this way!");
}

Archetype::Column::Column(Component component)
{
    this->component = std::move(component);
    this->elements = nullptr;
    this->count = 0;
    this->capacity = 0;
}


void* Archetype::Column::operator[](size_t index) const
{
    return (static_cast<char*>(elements) + component.size * index);
}

void* Archetype::Column::add(EntityID owner)
{
    count++;
    if (count > capacity)
    {
        if (capacity == 0)
            capacity = 1;
        capacity *= 2;
        if (elements == nullptr)
            elements = malloc(capacity * component.size);
        else
        {
            std::cout << "Capacity grown: " << this << " : " << count << " : " << capacity << " : " << component.name <<
                std::endl;
            void* newElements = malloc(capacity * component.size);
            //Move everything
            for (size_t i = 0; i < owners.size(); ++i)
            {
                if (owners[i] == 0)
                    continue; //No need to copy, it's not owned
                size_t offset = component.size * i;
                void* src = static_cast<char*>(elements) + offset;
                void* dst = static_cast<char*>(newElements) + offset;
                component.move(dst, src);
            }
            free(elements);
            elements = newElements;
        }
    }
    void* root = static_cast<char*>(elements) + (component.size * (count - 1));
    component.constructor(root);
    owners.push_back(owner);
    return root;
}

void* Archetype::Column::add(EntityID owner, void* instance)
{
    void* dest = add(owner);
    component.copy(dest, instance);
    return dest;
}

void Archetype::Column::remove(size_t index)
{
    owners[index] = 0; //AKA null entity
    //Destroy the data
    component.destructor(operator[](index));
}


Archetype::Edge::Edge(Archetype* add, Archetype* remove) : add(add),
                                                           remove(remove)
{
}

Archetype::Archetype(const Type& type)
{
    if (archetypeIndex.contains(type))
    {
        throw std::runtime_error("Cannot create two archetypes of the same type!");
    }
    this->id = archetypeIndex.size();
    this->type = type;
    for (int i = 0; i < type.size(); ++i)
    {
        components.emplace_back(type[i]);
        componentIndex[type[i]][this].column = i;
    }
    archetypeIndex.insert({this->type, this});
}

Archetype::Edge& Archetype::getEdge(const Component& component)
{
    if (edges.contains(component))
    {
        return edges.at(component);
    }
    Archetype* add = nullptr;
    Archetype* remove = nullptr;

    Type addType = type;
    auto addItem = std::find(addType.begin(), addType.end(), component);
    if (addItem == addType.end())
    {
        addType.push_back(component);

        add = archetypeIndex.insert({addType, getArchetype(addType)}).first->second;
    }

    Type removeType = type;
    auto removeItem = std::find(removeType.begin(), removeType.end(), component);
    if (removeItem != removeType.end())
    {
        removeType.erase(removeItem);

        remove = archetypeIndex.insert({removeType, getArchetype(removeType)}).first->second;
    }
    return edges.insert({component, {add, remove}}).first->second;
}

void Archetype::remove(size_t row)
{
    for (int i = 0; i < components.size(); ++i)
    {
        components[i].remove(row);
    }
}

size_t Archetype::add(EntityID owner)
{
    for (auto& column : components)
    {
        column.add(owner);
    }
    size_t row = 0;
    if (!components.empty())
        row = components[0].count - 1;
    return row;
}

Archetype* Archetype::getArchetype(const Type& type)
{
    if (archetypeIndex.contains(type))
    {
        return archetypeIndex.at(type);
    }


    archetypeIndex.insert({type, new Archetype{type}});
    return archetypeIndex.at(type);
}
