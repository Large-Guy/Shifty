#ifndef SHIFTY_VELOCITY_H
#define SHIFTY_VELOCITY_H

struct Motion
{
    float deltaX, deltaY;
    float deltaW, deltaH;
    float prevX, prevY;
    float prevW, prevH;
};

#endif //SHIFTY_VELOCITY_H
