#ifndef SHIFTY_TEXTEDITSYSTEMS_H
#define SHIFTY_TEXTEDITSYSTEMS_H
#include "Components/InputHandler.h"
#include "ECS/System.h"


class EditInput : System<OnTextInput>
{
    void process(const OnTextInput&) override;
};

class EditKeydown : System<OnKeyPress>
{
    void process(const OnKeyPress&) override;
};


#endif //SHIFTY_TEXTEDITSYSTEMS_H
