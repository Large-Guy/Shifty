#ifndef SHIFTY_APPCLOSE_H
#define SHIFTY_APPCLOSE_H
#include "ECS/System.h"
#include "Platform/EventHandler.h"


class AppClose : System<OnWindowClose>
{
    void process(const OnWindowClose&) override;
};


#endif //SHIFTY_APPCLOSE_H
