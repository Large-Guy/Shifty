//
// Created by Ravi Lebgue on 9/24/25.
//

#include "AppUpdate.h"

#include <stdexcept>


#include "../Components/App.h"
#include "../ECS/Entity.h"
#include "../Components/InputHandler.h"

#include <SDL3/SDL.h>

#include "RenderTransformsCompute.h"

void AppUpdate::process(const OnUpdate& _update)
{
    SDL_Event e;
    Entity app = Entity::findEntity<App>();
    ComRef<InputHandler> handler = app.get<InputHandler>();
    while (SDL_PollEvent(&e))
    {
        auto window = SDL_GetWindowFromID(e.window.windowID);
        if (handler->textInput != SDL_TextInputActive(window))
        {
            if (handler->textInput)
                SDL_StartTextInput(window);
            else
                SDL_StopTextInput(window);
        }

        switch (e.type)
        {
        case SDL_EVENT_QUIT:
            app.get<App>()->running = false;
        case SDL_EVENT_KEY_DOWN:
            handler->keyStates[e.key.key] = true;
            EventBus::emit(OnKeyPress{handler, e.key.key});
            break;
        case SDL_EVENT_KEY_UP:
            handler->keyStates[e.key.key] = false;
            EventBus::emit(OnKeyRelease{handler, e.key.key});
            break;
        case SDL_EVENT_TEXT_INPUT:
            EventBus::emit(OnTextInput{handler, e.text.text});
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            EventBus::emit(OnMouseButtonPress{handler, e.button.x, e.button.y, e.button.button});
        case SDL_EVENT_MOUSE_BUTTON_UP:
            EventBus::emit(OnMouseButtonRelease{handler, e.button.x, e.button.y, e.button.button});
        case SDL_EVENT_WINDOW_RESIZED:
            EventBus::emit(OnWindowResize{SDL_GetWindowFromID(e.window.windowID), e.window.data1, e.window.data2});
        default:
            break;
        }
    }

    int screenWidth, screenHeight;
    SDL_GetWindowSize(app.get<App>()->window.window, &screenWidth, &screenHeight);

    EventBus::emit<OnLayout>({0, 0, static_cast<float>(screenWidth), static_cast<float>(screenHeight)});
}
