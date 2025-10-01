#ifndef SHIFTY_RENDERTRANSFORM_H
#define SHIFTY_RENDERTRANSFORM_H


struct RenderTransform
{
    float x, y;
    float w, h;

    bool overrideX;
    bool overrideY;
    bool overrideW;
    bool overrideH;
    float overriddenX;
    float overriddenY;
    float overriddenW;
    float overriddenH;
};


#endif //SHIFTY_RENDERTRANSFORM_H
