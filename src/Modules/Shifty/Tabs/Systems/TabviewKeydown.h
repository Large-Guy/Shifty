#ifndef SHIFTY_TABVIEWKEYDOWN_H
#define SHIFTY_TABVIEWKEYDOWN_H
#include "Platform/EventHandler.h"
#include "ECS/System.h"

class TabviewKeydown : System<OnKeyPress>
{
    void process(const OnKeyPress&) override;
};

#endif //SHIFTY_TABVIEWKEYDOWN_H