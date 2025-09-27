#ifndef SHIFTY_TRANSFORM_H
#define SHIFTY_TRANSFORM_H


struct Transform {
    enum class Mode {
        Pixel,
        Percent
    };

    Mode xMode = Mode::Percent;
    Mode yMode = Mode::Percent;
    float x, y;
    Mode wMode = Mode::Percent;
    Mode hMode = Mode::Percent;
    float w, h;
};


#endif //SHIFTY_TRANSFORM_H