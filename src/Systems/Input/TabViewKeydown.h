#ifndef SHIFTY_TABVIEWKEYDOWN_H
#define SHIFTY_TABVIEWKEYDOWN_H
#include "Components/InputHandler.h"
#include "ECS/System.h"

class TabViewKeydown : System<OnKeyPress>
{
    void process(const OnKeyPress&) override;
};

#endif //SHIFTY_TABVIEWKEYDOWN_H
