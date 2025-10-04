#ifndef SHIFTY_TABVIEWSTATE_H
#define SHIFTY_TABVIEWSTATE_H

struct TabviewState
{
    bool active;
    Entity targetView;
    int page = 0;
    Entity focusedTab;
};

#endif //SHIFTY_TABVIEWSTATE_H
