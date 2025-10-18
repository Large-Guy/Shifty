#ifndef SHIFTY_DRAWCREATE_H
#define SHIFTY_DRAWCREATE_H
#include "Drawing/Components/Draw.h"
#include "ECS/Entity.h"
#include "ECS/System.h"


class DrawCreate final : System<OnComponentCreate<Draw>>
{
    void process(const OnComponentCreate<Draw>&) override;
};


#endif //SHIFTY_DRAWCREATE_H