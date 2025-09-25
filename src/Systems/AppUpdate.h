//
// Created by Ravi Lebgue on 9/24/25.
//

#ifndef SHIFTY_APPUPDATE_H
#define SHIFTY_APPUPDATE_H
#include "../Events.h"
#include "../ECS/Entity.h"

class AppUpdate : System<OnUpdate> {
public:
    void process(const OnUpdate &_update);
};

#endif //SHIFTY_APPUPDATE_H
