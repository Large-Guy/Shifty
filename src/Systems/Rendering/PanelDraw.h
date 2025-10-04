#ifndef SHIFTY_PANELVIEWDRAW_H
#define SHIFTY_PANELVIEWDRAW_H
#include "Components/Draw.h"
#include "Components/RenderTransform.h"
#include "ECS/System.h"

class PanelDraw : public System<OnDraw>
{
    struct Command : public Draw::Command
    {
        ComRef<RenderTransform> renderTransform;

        Command(ComRef<RenderTransform> renderTransform);

        void execute(SDL_Renderer* renderer) override;
    };


    void process(const OnDraw&) override;
};

#endif //SHIFTY_PANELVIEWDRAW_H
