#include "AppCreate.h"

void AppCreate::process(const OnComponentCreate<App>& component)
{
    auto app = component.component;
    app->window.open();
}
