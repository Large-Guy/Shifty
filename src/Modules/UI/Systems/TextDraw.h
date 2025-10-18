#ifndef SHIFTY_TEXTDRAW_H
#define SHIFTY_TEXTDRAW_H
#include "Drawing/Components/Draw.h"
#include "ECS/System.h"
#include "UI/Components/Text.h"


class TextDraw : public System<OnDraw>
{
public:
    class Command : public Draw::Command
    {
    public:
        SDL_FRect render;
        ComRef<Text> text;

        Command(SDL_FRect render, ComRef<Text> text);
        void execute(SDL_Renderer* renderer) override;
    };

    void process(const OnDraw&) override;
};


#endif //SHIFTY_TEXTDRAW_H
