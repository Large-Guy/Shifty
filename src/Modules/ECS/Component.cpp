#include "Component.h"

bool Component::operator==(const Component& other) const
{
    return this->id == other.id;
}
