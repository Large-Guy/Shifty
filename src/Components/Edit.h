#ifndef SHIFTY_TEXTEDIT_H
#define SHIFTY_TEXTEDIT_H
#include <cstdint>
#include <string>


struct Edit
{
    size_t cursor = 0;

    bool highlighting = false;
    size_t highlightStart = 0;
};


#endif //SHIFTY_TEXTEDIT_H
