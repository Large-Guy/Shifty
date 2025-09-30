#ifndef SHIFTY_VIEWDRAW_H
#define SHIFTY_VIEWDRAW_H
#include "Components/Draw.h"
#include "Components/Draw.h"
#include "Components/Draw.h"
#include "Components/RenderTransform.h"
#include "Components/View.h"
#include "ECS/System.h"


class ViewDraw final : System<OnDraw>
{
    struct Command : public Draw::Command
    {
        ComRef<View> view;
        ComRef<RenderTransform> renderTransform;

        Command(ComRef<RenderTransform> renderTransform, ComRef<View> view);

        void execute(SDL_Renderer* renderer) override;
    };

    struct DebugRenderTransform : public Draw::Command
    {
        ComRef<RenderTransform> renderTransform;

        DebugRenderTransform(ComRef<RenderTransform> renderTransform);

        void execute(SDL_Renderer* renderer) override;
    };

    void process(const OnDraw&) override;
};


#endif //SHIFTY_VIEWDRAW_H
