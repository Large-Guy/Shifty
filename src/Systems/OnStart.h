#ifndef SHIFTY_START_H
#define SHIFTY_START_H
#include "../Events.h"
#include "../ECS/System.h"


class OnStart final : System<OnReady> {
    void process(const OnReady&) override;
};


#endif //SHIFTY_START_H
