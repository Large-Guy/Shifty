#ifndef SHIFTY_TABVIEWDRAW_H
#define SHIFTY_TABVIEWDRAW_H
#include "Components/Draw.h"
#include "Components/RenderTransform.h"
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


    void process(const OnDraw&) override;
};


#endif //SHIFTY_TABVIEWDRAW_H
