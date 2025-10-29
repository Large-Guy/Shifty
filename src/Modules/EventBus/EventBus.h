#ifndef SHIFTY_EVENTBUS_H
#define SHIFTY_EVENTBUS_H
#include <functional>
#include <iostream>
#include <typeindex>

template <typename T, typename = int>
struct HasConsumed : std::false_type
{
};

template <typename T>
struct HasConsumed<T, decltype((void)T::consumed, 0)> : std::true_type
{
};

class EventBus
{
    static std::unordered_map<std::type_index, std::vector<std::function<void(void*)>>> connections;

    template <typename Event>
    using Handler = std::function<void(Event&)>;

public:
    template <typename Event>
    static void subscribe(Handler<Event> handler)
    {
        auto& handlers = connections[typeid(Event)];
        handlers.push_back([handler = std::move(handler)](void* e)
        {
            if (!handler)
                return;
            Event& event = *static_cast<Event*>(e);
            handler(event);
        });
    }

    template <typename Event>
    static void unsubscribe(Handler<Event> handler)
    {
    }

    template <typename Event>
    static void emit(Event event)
    {
        if constexpr (HasConsumed<Event>::value == true)
        {
            event.consumed = false;
        }
        auto it = connections.find(typeid(Event));
        if (it == connections.end()) return;
        for (auto& handler : it->second)
        {
            if constexpr (HasConsumed<Event>::value == true)
            {
                if (event.consumed)
                {
                    std::cout << "Got consumed" << std::endl;
                    break;
                }
            }

            handler(&event);
        }
    }
};

#endif //SHIFTY_EVENTBUS_H
