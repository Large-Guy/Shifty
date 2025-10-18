#ifndef SHIFTY_DRAWRESIZE_H
#define SHIFTY_DRAWRESIZE_H
#include "ECS/System.h"
#include "Platform/EventHandler.h"


class DrawResize : System<OnWindowResize>
{
    void process(const OnWindowResize&) override;
};


#endif //SHIFTY_DRAWRESIZE_H
