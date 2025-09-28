//
// Created by ravilebgue on 9/27/25.
//

#ifndef SHIFTY_TEXTDRAW_H
#define SHIFTY_TEXTDRAW_H
#include "Components/Draw.h"
#include "Components/Text.h"
#include "ECS/System.h"


class TextCommand : public Draw::Command
{
public:
    float x, y, w, h;
    Text text;

    TextCommand(float x, float y, float w, float h, const Text& text);
    void execute(SDL_Renderer* renderer) override;
};

class TextDraw : public System<OnDraw>
{
    void process(const OnDraw&) override;
};


#endif //SHIFTY_TEXTDRAW_H
