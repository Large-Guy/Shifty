#ifndef SHIFTY_TEXTEDITSYSTEMS_H
#define SHIFTY_TEXTEDITSYSTEMS_H
#include "Events.h"
#include "Components/Draw.h"
#include "Components/Edit.h"
#include "Components/InputHandler.h"
#include "Components/RenderTransform.h"
#include "Components/Text.h"
#include "ECS/System.h"


class EditInput final : System<OnTextInput>
{
    void process(const OnTextInput&) override;
};

class EditKeydown final : System<OnKeyPress>
{
    void process(const OnKeyPress&) override;
};

class EditProcess final : System<OnUpdate>
{
    void process(const OnUpdate&) override;
};

class EditDraw final : System<OnDraw>
{
    class Command : public Draw::Command
    {
    public:
        SDL_FRect render;
        ComRef<Text> text;
        ComRef<Edit> edit;
        Command(SDL_FRect render, ComRef<Text> text, ComRef<Edit> edit);
        void execute(SDL_Renderer* renderer) override;
    };

    void process(const OnDraw&) override;
};

#endif //SHIFTY_TEXTEDITSYSTEMS_H
