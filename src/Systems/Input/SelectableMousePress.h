#ifndef SHIFTY_SELECTABLEMOUSEPRESS_H
#define SHIFTY_SELECTABLEMOUSEPRESS_H
#include "Components/InputHandler.h"
#include "ECS/System.h"


class SelectableMousePress : System<OnMouseButtonPress>
{
public:
    void process(const OnMouseButtonPress&) override;
};


#endif //SHIFTY_SELECTABLEMOUSEPRESS_H
