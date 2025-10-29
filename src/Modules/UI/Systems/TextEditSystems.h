#ifndef SHIFTY_TEXTEDITSYSTEMS_H
#define SHIFTY_TEXTEDITSYSTEMS_H
#include "EventBus/StandardEvents.h"
#include "Drawing/Components/Draw.h"
#include "Platform/EventHandler.h"
#include "ECS/System.h"
#include "UI/Components/Edit.h"
#include "UI/Components/Text.h"


class EditInput final : System<OnTextInput>
{
    void process(OnTextInput&) override;
};

class EditKeydown final : System<OnKeyPress>
{
    void process(OnKeyPress&) override;
};

class EditProcess final : System<OnUpdate>
{
    void process(OnUpdate&) override;
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

    void process(OnDraw&) override;
};

#endif //SHIFTY_TEXTEDITSYSTEMS_H
