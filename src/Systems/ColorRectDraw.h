#ifndef SHIFTY_COLORRECTDRAW_H
#define SHIFTY_COLORRECTDRAW_H
#include "../Components/Draw.h"
#include "../ECS/System.h"

struct RectCommand : public Draw::Command {
    SDL_FRect& rect;
    SDL_Color& color;

    RectCommand(int priority, SDL_FRect& rect, SDL_Color& color);

    void execute(SDL_Renderer* renderer) override;
};

class ColorRectDraw : System<OnDraw> {
    void process(const OnDraw&) override;
};


#endif //SHIFTY_COLORRECTDRAW_H