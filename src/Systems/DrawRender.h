#ifndef SHIFTY_DRAWRENDER_H
#define SHIFTY_DRAWRENDER_H
#include "../ECS/System.h"
#include "../Events.h"

class DrawRender : System<OnRender> {
    void process(const OnRender &) override;
};


#endif //SHIFTY_DRAWRENDER_H
