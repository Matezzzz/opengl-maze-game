#ifndef BASE_FRAMEBUFFER_H
#define BASE_FRAMEBUFFER_H

#include "texture.h"
#include "base_object.h"
#include <my_own/old/glprogram.h>
//#include <my_own/glprogram.h>

class BaseFramebuffer
{
    unsigned int m_framebuffer;
    int m_width, m_height;
protected:
    void checkFramebuffer();
public:
    BaseFramebuffer(int width, int height);
    void use();
    void unuse();
    void setViewport();
    static unsigned int makeRenderbuffer(int width, int height);
};


class ColorFramebuffer : public BaseFramebuffer
{
    unsigned int m_color_texture;
    unsigned int m_depth_renderbuffer;
public:
    ColorFramebuffer(int width, int height, BaseTexture color_texture);
    unsigned int getColorTexture();
};

class ShadowFramebuffer : public BaseFramebuffer
{
    unsigned int m_depth_texture;
public:
    ShadowFramebuffer(int width, int height);
    unsigned int getDepthTexture();
};
#endif // BASE_FRAMEBUFFER_H

