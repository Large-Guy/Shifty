#include "EventBus.h"

namespace Shifty {
    std::unordered_map<std::type_index, std::vector<std::function<void(const void *)> > > EventBus::connections = {};
} // Shifty
