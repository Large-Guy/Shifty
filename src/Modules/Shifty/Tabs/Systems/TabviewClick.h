#ifndef SHIFTY_TABVIEWCLICK_H
#define SHIFTY_TABVIEWCLICK_H
#include "Platform/EventHandler.h"
#include "ECS/System.h"

class TabviewClick : System<OnMouseButtonPress>
{
    void process(OnMouseButtonPress&) override;
};

#endif //SHIFTY_TABVIEWCLICK_H
