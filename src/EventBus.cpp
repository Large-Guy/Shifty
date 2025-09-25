#include "EventBus.h"

std::unordered_map<std::type_index, std::vector<std::function<void(const void *)> > > EventBus::connections = {};
