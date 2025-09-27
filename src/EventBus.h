//
// Created by ravilebgue on 9/22/25.
//

#ifndef SHIFTY_EVENTBUS_H
#define SHIFTY_EVENTBUS_H
#include <functional>
#include <typeindex>

class EventBus {
    static std::unordered_map<std::type_index, std::vector<std::function<void(const void*)>>> connections;

    template<typename Event>
    using Handler = std::function<void(const Event&)>;

public:
    template<typename Event>
    static void subscribe(Handler<Event> handler) {
        auto& handlers = connections[typeid(Event)];
        handlers.push_back([handler = std::move(handler)](const void* e) {
            if (!handler)
                return;
            handler(*static_cast<const Event*>(e));
        });
    }

    template<typename Event>
    static void unsubscribe(Handler<Event> handler) {
    }

    template<typename Event>
    static void emit(const Event& event) {
        auto it = connections.find(typeid(Event));
        if (it == connections.end()) return;
        for (auto& handler : it->second) {
            handler(&event);
        }
    }
};

#endif //SHIFTY_EVENTBUS_H
