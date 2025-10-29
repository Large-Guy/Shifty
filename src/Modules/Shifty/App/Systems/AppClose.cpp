#include "AppClose.h"

#include <iostream>

#include "ECS/Entity.h"
#include "Shifty/App/Components/App.h"

void AppClose::process(OnWindowClose& close)
{
    if (close.window == Entity::find<App>()->window->window)
    {
        Entity::find<App>()->running = false;
        std::cout << "Closing" << std::endl;
    }
}
