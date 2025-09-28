//
// Created by ravilebgue on 9/27/25.
//

#ifndef SHIFTY_TEXTDRAW_H
#define SHIFTY_TEXTDRAW_H
#include "Components/Draw.h"
#include "Components/RenderTransform.h"
#include "Components/Text.h"
#include "ECS/System.h"


class TextDraw : public System<OnDraw>
{
public:
    class Command : public Draw::Command
    {
    public:
        SDL_FRect render;
        Text& text;

        Command(SDL_FRect render, Text& text);
        void execute(SDL_Renderer* renderer) override;
    };

    void process(const OnDraw&) override;
};


#endif //SHIFTY_TEXTDRAW_H
