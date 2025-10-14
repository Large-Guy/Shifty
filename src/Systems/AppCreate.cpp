#include "AppCreate.h"

void AppCreate::process(const OnComponentCreate<App>& component)
{
    auto app = component.component;
    app->window = std::make_shared<Window>("Shifty", 1080, 720);
}
