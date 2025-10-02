#ifndef SHIFTY_NAVIGATIONUPDATE_H
#define SHIFTY_NAVIGATIONUPDATE_H
#include "Events.h"
#include "Components/InputHandler.h"
#include "ECS/System.h"


class TabViewKeydown : System<OnKeyPress>
{
    void process(const OnKeyPress&) override;
};

class TabViewUpdate : System<OnUpdate>
{
    void process(const OnUpdate&) override;
};

class TabViewClick : System<OnMouseButtonPress>
{
    void process(const OnMouseButtonPress&) override;
};

#endif //SHIFTY_NAVIGATIONUPDATE_H
