#ifndef SHIFTY_TABVIEWCLICK_H
#define SHIFTY_TABVIEWCLICK_H
#include "Components/InputHandler.h"
#include "ECS/System.h"

class TabviewClick : System<OnMouseButtonPress>
{
    void process(const OnMouseButtonPress&) override;
};

#endif //SHIFTY_TABVIEWCLICK_H
