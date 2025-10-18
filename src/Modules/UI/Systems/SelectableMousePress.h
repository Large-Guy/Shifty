#ifndef SHIFTY_SELECTABLEMOUSEPRESS_H
#define SHIFTY_SELECTABLEMOUSEPRESS_H
#include "Platform/EventHandler.h"
#include "ECS/System.h"


class SelectableMousePress : System<OnMouseButtonPress>
{
public:
    void process(const OnMouseButtonPress&) override;
};


#endif //SHIFTY_SELECTABLEMOUSEPRESS_H
