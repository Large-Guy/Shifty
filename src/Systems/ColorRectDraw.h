#ifndef SHIFTY_COLORRECTDRAW_H
#define SHIFTY_COLORRECTDRAW_H
#include "../Components/Draw.h"
#include "../ECS/System.h"


class ColorRectDraw : System<OnDraw>
{
public:
    struct Command : public Draw::Command
    {
        SDL_FRect rect;
        SDL_Color color;

        Command(int priority, SDL_FRect rect, SDL_Color color);

        void execute(SDL_Renderer* renderer) override;
    };

    void process(const OnDraw&) override;
};


#endif //SHIFTY_COLORRECTDRAW_H
