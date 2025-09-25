#ifndef SHIFTY_APPCREATE_H
#define SHIFTY_APPCREATE_H
#include "../Components/App.h"
#include "../ECS/Entity.h"
#include "../ECS/System.h"


class AppCreate final : System<OnComponentCreate<App> > {
    void process(const OnComponentCreate<App>&) override;
};


#endif //SHIFTY_APPCREATE_H
