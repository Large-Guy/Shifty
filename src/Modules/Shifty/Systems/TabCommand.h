#ifndef SHIFTY_SPLITCOMMAND_H
#define SHIFTY_SPLITCOMMAND_H
#include "ECS/System.h"
#include "Shifty/CommandPalette/Components/CommandPalette.h"


class TabCommand final : System<OnCommandExecute>
{
    void process(const OnCommandExecute&) override;
};


#endif //SHIFTY_SPLITCOMMAND_H
