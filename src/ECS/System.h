#ifndef SHIFTY_SYSTEM_H
#define SHIFTY_SYSTEM_H

#include "../EventBus.h"

///@class System
///This encourages systems to do ONE THING ONLY keeping code more modular.
///Only ONE event should be subscribed to per system.
template<typename T>
class System {
public:
    virtual void process(const T&) {
    }

    System() {
        EventBus::subscribe<T>([this](T event) {
            this->process(event);
        });
    }

    virtual ~System() {
    }
};


#endif //SHIFTY_SYSTEM_H
