#ifndef SHIFTY_SPLITCOMMAND_H
#define SHIFTY_SPLITCOMMAND_H
#include "Components/CommandPalette.h"
#include "ECS/System.h"


class SplitCommand final : System<OnCommandExecute>
{
    void process(const OnCommandExecute&) override;
};


#endif //SHIFTY_SPLITCOMMAND_H
