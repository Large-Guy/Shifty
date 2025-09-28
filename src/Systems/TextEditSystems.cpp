#include "TextEditSystems.h"

#include "Components/Edit.h"
#include "Components/Focus.h"
#include "Components/Text.h"
#include "ECS/Entity.h"

void EditInput::process(const OnTextInput& input)
{
    Entity::multiEach<Focus, Text, Edit>([input](Focus& focus, Text& text, Edit& edit)
    {
        if (edit.highlighting)
        {
            //TODO: Delete text
        }
        text.text.insert(edit.cursor, input.input);
        edit.cursor += input.input.length();
    });
}

void EditKeydown::process(const OnKeyPress& input)
{
    switch (input.key)
    {
    case SDLK_BACKSPACE:
        {
            Entity::multiEach<Focus, Text, Edit>([input](Focus& focus, Text& text, Edit& edit)
            {
                if (edit.highlighting)
                {
                    //TODO: Delete highlight/selection
                }
                else if (edit.cursor > 0)
                {
                    if (input.handler.isPressed(SDLK_LCTRL) || input.handler.isPressed(SDLK_RCTRL))
                    {
                        //Delete word
                    }
                    else
                    {
                        text.text.erase(edit.cursor - 1, 1);
                        edit.cursor--;
                    }
                }
            });
            break;
        }
    case SDLK_DELETE:
        {
            Entity::multiEach<Focus, Text, Edit>([input](Focus& focus, Text& text, Edit& edit)
            {
                if (edit.highlighting)
                {
                    //TODO: Delete highlight/selection
                }
                else if (edit.cursor > 0)
                {
                    if (input.handler.isPressed(SDLK_LCTRL) || input.handler.isPressed(SDLK_RCTRL))
                    {
                        //Delete word
                    }
                    else
                    {
                        text.text.erase(edit.cursor - 1, 1);
                        edit.cursor--;
                    }
                }
            });
            break;
        }
    case SDLK_LEFT:
        {
            Entity::multiEach<Focus, Text, Edit>([input](Focus& focus, Text& text, Edit& edit)
            {
                if (input.handler.isPressed(SDLK_LSHIFT) || input.handler.isPressed(SDLK_RSHIFT))
                {
                    //TODO: Highlight
                }
                else
                {
                    //TODO: Clear selection
                }

                if (!edit.cursor > 0)
                    return;

                if (input.handler.isPressed(SDLK_LCTRL) || input.handler.isPressed(SDLK_RCTRL))
                {
                    //Move by word
                }
                else
                {
                    edit.cursor--;
                }
            });
            break;
        }
    case SDLK_RIGHT:
        {
            Entity::multiEach<Focus, Text, Edit>([input](Focus& focus, Text& text, Edit& edit)
            {
                if (input.handler.isPressed(SDLK_LSHIFT) || input.handler.isPressed(SDLK_RSHIFT))
                {
                    //TODO: Highlight
                }
                else
                {
                    //TODO: Clear selection
                }

                if (edit.cursor >= text.text.length())
                    return;

                if (input.handler.isPressed(SDLK_LCTRL) || input.handler.isPressed(SDLK_RCTRL))
                {
                    //Move by word
                }
                else
                {
                    edit.cursor++;
                }
            });
            break;
        }
    }
}
