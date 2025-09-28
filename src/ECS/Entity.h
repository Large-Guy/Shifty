#ifndef SHIFTY_ENTITY_H
#define SHIFTY_ENTITY_H

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <stdexcept>

#include "Component.h"
#include "Archetype.h"
#include "../EventBus.h"

using EntityID = uint32_t;

template <typename T>
struct OnComponentCreate
{
    EntityID entity;
    T& component;
};

class Entity
{
    struct Record
    {
        Archetype* archetype;
        size_t row;
    };

    static std::unordered_map<EntityID, Record> entityIndex;
    static EntityID count;

    void move(Archetype* current, size_t row, Archetype* next);

public:
    EntityID id;

    Entity(EntityID id = 0);

    bool operator==(const Entity& other) const;
    bool operator==(EntityID other) const;
    bool operator==(std::nullptr_t other) const;

    static Entity create();

    bool has(Component component) const;

    void* get(Component component) const;

    void* add(Component component, void* instance = nullptr);

    void remove(Component component);

    template <typename T>
    bool has() const
    {
        return has(Component::get<T>());
    }

    template <typename T>
    T& get() const
    {
        return *static_cast<T*>(get(Component::get<T>()));
    }

    template <typename T>
    T& add()
    {
        T* component = static_cast<T*>(add(Component::get<T>()));
        OnComponentCreate<T> event{id, *component};
        EventBus::emit(event);
        return *component;
    }

    template <typename T>
    T& add(T instance)
    {
        T* component = static_cast<T*>(add(Component::get<T>(), &instance));
        OnComponentCreate<T> event{id, *component};
        EventBus::emit(event);
        return *component;
    }

    template <typename T>
    void remove()
    {
        remove(Component::get<T>());
    }

    template <typename T>
    static void each(std::function<void(T&)> callback, std::function<bool(T&)> filter = nullptr)
    {
        Archetype::Map& map = Archetype::componentIndex[Component::get<T>()];
        for (auto& element : map)
        {
            auto& column = element.first->components[element.second.column];
            for (size_t i = 0; i < column.count; ++i)
            {
                Entity entity = column.owners[i];
                if (entity.id == 0)
                    continue;

                if (filter && !filter(*static_cast<T*>(column[i])))
                    continue;
                callback(*static_cast<T*>(column[i]));
            }
        }
    }

    template <typename... Args, typename Func>
    static void multiEach(Func callback)
    {
        std::vector<Component> components = {Component::get<Args>()...};

        Archetype::Map& map = Archetype::componentIndex[components[0]];
        std::unordered_map<Component, Archetype::Column, ComponentHash> columns;
        for (auto& element : map)
        {
            columns.clear();
            auto& column = element.first->components[element.second.column];
            bool containsAll = true;
            for (auto component : components)
            {
                auto contains = Archetype::componentIndex[component].contains(element.first);
                if (!contains)
                {
                    containsAll = false;
                    break;
                }
                columns.insert({
                    component, element.first->components[Archetype::componentIndex[component][element.first].
                        column]
                });
            }

            if (!containsAll)
                continue;

            for (size_t i = 0; i < column.count; ++i)
            {
                Entity entity = column.owners[i];

                if (entity.id == 0)
                    continue;

                int index = 0;
                auto getComponent = [&]()
                {
                    return columns[components[index++]][i];
                };

                if constexpr (std::is_invocable_v<Func, Entity, decltype(*static_cast<Args*>(getComponent()))...>)
                {
                    // Function takes (Entity, Component)
                    callback(entity, *static_cast<Args*>(getComponent())...);
                }
                else if constexpr (std::is_invocable_v<Func, decltype(*static_cast<Args*>(getComponent()))...>)
                {
                    // Function takes just (Component)
                    callback(*static_cast<Args*>(getComponent())...);
                }
            }
        }
    }

    template <typename... Args, typename Func, typename Filter>
    static void multiEach(Func callback, Filter filter)
    {
        std::vector<Component> components = {Component::get<Args>()...};

        Archetype::Map& map = Archetype::componentIndex[components[0]];
        std::unordered_map<Component, Archetype::Column, ComponentHash> columns;
        for (auto& element : map)
        {
            columns.clear();
            auto& column = element.first->components[element.second.column];
            bool containsAll = true;
            for (auto component : components)
            {
                auto contains = Archetype::componentIndex[component].contains(element.first);
                if (!contains)
                {
                    containsAll = false;
                    break;
                }
                columns.insert({
                    component, element.first->components[Archetype::componentIndex[component][element.first].
                        column]
                });
            }

            if (!containsAll)
                continue;

            for (size_t i = 0; i < column.count; ++i)
            {
                Entity entity = column.owners[i];

                if (entity.id == 0)
                    continue;

                int index = 0;
                auto getComponent = [&]()
                {
                    return columns[components[index++]][i];
                };

                if (!filter(entity, *static_cast<Args*>(getComponent())...))
                    continue;

                index = 0;

                if constexpr (std::is_invocable_v<Func, Entity, decltype(*static_cast<Args*>(getComponent()))...>)
                {
                    // Function takes (Entity, Component)
                    callback(entity, *static_cast<Args*>(getComponent())...);
                }
                else if constexpr (std::is_invocable_v<Func, decltype(*static_cast<Args*>(getComponent()))...>)
                {
                    // Function takes just (Component)
                    callback(*static_cast<Args*>(getComponent())...);
                }
            }
        }
    }

    template <typename T>
    static void each(std::function<void(Entity entity, T&)> callback, std::function<bool(T&)> filter = nullptr)
    {
        Archetype::Map& map = Archetype::componentIndex[Component::get<T>()];
        for (auto& element : map)
        {
            auto& column = element.first->components[element.second.column];
            for (size_t i = 0; i < column.count; ++i)
            {
                Entity entity = column.owners[i];
                if (entity.id == 0)
                    continue;

                if (filter && !filter(*static_cast<T*>(column[i])))
                    continue;
                callback(entity, *static_cast<T*>(column[i]));
            }
        }
    }

    template <typename T>
    static Entity findEntity()
    {
        const Archetype::Map& map = Archetype::componentIndex[Component::get<T>()];
        for (auto& element : map)
        {
            auto& column = element.first->components[element.second.column];
            for (size_t i = 0; i < column.count; ++i)
            {
                if (column.owners[i] == 0)
                    continue;
                return column.owners[i];
            }
        }
        return {0};
    }

    template <typename T>
    static T& find()
    {
        const Archetype::Map& map = Archetype::componentIndex[Component::get<T>()];
        for (auto& element : map)
        {
            auto& column = element.first->components[element.second.column];
            for (size_t i = 0; i < column.count; ++i)
            {
                if (column.owners[i] == 0)
                    continue;
                return *static_cast<T*>(column[i]);
            }
        }
        throw std::runtime_error("Entity not found with component");
    }

    template <typename T>
    static bool exists()
    {
        const Archetype::Map& map = Archetype::componentIndex[Component::get<T>()];
        for (auto& element : map)
        {
            auto& column = element.first->components[element.second.column];
            for (size_t i = 0; i < column.count; ++i)
            {
                if (column.owners[i] == 0)
                    continue;
                return true;
            }
        }
        return false;
    }
};

#endif //SHIFTY_ENTITY_H
