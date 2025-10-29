#ifndef SHIFTY_TABVIEWDRAW_H
#define SHIFTY_TABVIEWDRAW_H
#include "Drawing/Components/Draw.h"
#include "Drawing/Components/RenderTransform.h"
#include "ECS/System.h"


class TabviewDraw : public System<OnDraw>
{
    struct Command : public Draw::Command
    {
        ComRef<RenderTransform> renderTransform;
        float alpha;

        Command(ComRef<RenderTransform> renderTransform, float alpha);

        void execute(SDL_Renderer* renderer) override;
    };


    void process(OnDraw&) override;
};


#endif //SHIFTY_TABVIEWDRAW_H
