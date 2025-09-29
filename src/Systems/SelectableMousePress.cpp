#include "SelectableMousePress.h"

#include <iostream>

#include "Components/Focus.h"
#include "Components/Layout.h"
#include "Components/RenderTransform.h"
#include "Components/Selectable.h"
#include "ECS/Entity.h"

void SelectableMousePress::process(const OnMouseButtonPress& press)
{
    if (press.button == SDL_BUTTON_LEFT)
    {
        bool selectedSomething = false;
        Entity::multiEach<Selectable, RenderTransform>(
            [press, &selectedSomething](Entity entity, Selectable& selectable, RenderTransform& transform)
            {
                if (selectedSomething)
                    return;

                if (transform.x <= press.x && press.x <= transform.x + transform.w && transform.y <= press.y && press.y
                    <=
                    transform.y + transform.h)
                {
                    std::cout << "Focused " << entity.id << std::endl;
                    Entity::find<Focus>().focused = entity;
                    selectedSomething = true;
                }
            });
    }
}
