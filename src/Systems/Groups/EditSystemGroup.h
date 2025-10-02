#ifndef SHIFTY_EDITGROUP_H
#define SHIFTY_EDITGROUP_H
#include "Systems/TextEditSystems.h"

struct EditSystemGroup
{
    EditProcess editProcess{};
    EditInput editInput{};
    EditKeydown editKeydown{};
    EditDraw editDraw{};
};

#endif //SHIFTY_EDITGROUP_H
