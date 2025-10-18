#ifndef SHIFTY_TRANSFORM_H
#define SHIFTY_TRANSFORM_H


struct Transform
{
    enum class Mode
    {
        Auto,
        Pixel,
        Percent,
        Absolute,
    };

    Mode xMode = Mode::Auto;
    Mode yMode = Mode::Auto;
    float x = 0.0f, y = 0.0f;
    Mode wMode = Mode::Auto;
    Mode hMode = Mode::Auto;
    float w = 1.0f, h = 1.0f;
};


#endif //SHIFTY_TRANSFORM_H
