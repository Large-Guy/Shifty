#ifndef SHIFTY_PANELVIEWDRAW_H
#define SHIFTY_PANELVIEWDRAW_H
#include "Drawing/Components/Draw.h"
#include "Drawing/Components/RenderTransform.h"
#include "ECS/System.h"

class PaneDraw : public System<OnDraw>
{
    struct Command : public Draw::Command
    {
        ComRef<RenderTransform> renderTransform;

        Command(ComRef<RenderTransform> renderTransform);

        void execute(SDL_Renderer* renderer) override;
    };


    void process(OnDraw&) override;
};

#endif //SHIFTY_PANELVIEWDRAW_H
