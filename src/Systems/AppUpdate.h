//
// Created by Ravi Lebgue on 9/24/25.
//

#ifndef SHIFTY_APPUPDATE_H
#define SHIFTY_APPUPDATE_H
#include "../Events.h"
#include "../ECS/Entity.h"

namespace Shifty {
    class AppUpdate : ECS::System<OnUpdate> {
    public:
        void process(const OnUpdate& _update);
    };
} // Shifty

#endif //SHIFTY_APPUPDATE_H
