#ifndef SHIFTY_APPCREATE_H
#define SHIFTY_APPCREATE_H

#include "ECS/Entity.h"
#include "ECS/System.h"
#include "Shifty/App/Components/App.h"

class AppCreate final : System<OnComponentCreate<App>>
{
    void process(OnComponentCreate<App>&) override;
};


#endif //SHIFTY_APPCREATE_H
