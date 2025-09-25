#include "Component.h"

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
