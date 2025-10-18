#include "AppUpdate.h"

#include "Shifty/App/Components/App.h"

#include <SDL3/SDL.h>

#include "ECS/Entity.h"
#include "UI/Systems/RenderTransformsCompute.h"
#include "EventBus/EventBus.h"

void AppUpdate::process(const OnUpdate& _update)
{
    SDL_Event e;

    int screenWidth, screenHeight;
    SDL_GetWindowSize(Entity::find<App>()->window->window, &screenWidth, &screenHeight);

    Entity::find<App>()->handler->pollEvents();

    EventBus::emit<OnLayout>({0, 0, static_cast<float>(screenWidth), static_cast<float>(screenHeight)});
}
