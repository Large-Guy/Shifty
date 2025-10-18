#ifndef SHIFTY_VIEWDRAW_H
#define SHIFTY_VIEWDRAW_H
#include "Drawing/Components/Draw.h"
#include "Drawing/Components/RenderTransform.h"
#include "ECS/System.h"
#include "Shifty/Tabs/Components/Tab.h"
#include "UI/Components/Motion.h"


class TabDraw final : System<OnDraw>
{
    struct Command : public Draw::Command
    {
        ComRef<Tab> tab;
        ComRef<RenderTransform> renderTransform;
        ComRef<Motion> motion;

        Command(ComRef<RenderTransform> renderTransform, ComRef<Motion> motion, ComRef<Tab> tab, int layer);

        void execute(SDL_Renderer* renderer) override;
    };


    void process(const OnDraw&) override;
};


#endif //SHIFTY_VIEWDRAW_H