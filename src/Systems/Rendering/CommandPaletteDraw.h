#ifndef SHIFTY_COMMANDPALETTEDRAW_H
#define SHIFTY_COMMANDPALETTEDRAW_H
#include "Components/Draw.h"
#include "Components/RenderTransform.h"
#include "ECS/System.h"


class CommandPaletteDraw : System<OnDraw>
{
    struct Command : public Draw::Command
    {
        ComRef<RenderTransform> transform;
        Command(ComRef<RenderTransform> transform);

        void execute(SDL_Renderer* renderer) override;
    };

    void process(const OnDraw&) override;
};


#endif //SHIFTY_COMMANDPALETTEDRAW_H
