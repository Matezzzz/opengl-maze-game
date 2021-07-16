#include "base_framebuffer.h"
#include "texture.h"
#include "glad.h"
#include <iostream>


BaseFramebuffer::BaseFramebuffer(int width, int height) : m_framebuffer(-1), m_width(width), m_height(height)
{
    glGenFramebuffers(1, &m_framebuffer);
}

void BaseFramebuffer::checkFramebuffer()
{
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "Can't create frame buffer.\n";
    }
}
void BaseFramebuffer::use()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
}

void BaseFramebuffer::unuse()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void BaseFramebuffer::setViewport()
{
    glViewport(0, 0, m_width, m_height);
}

unsigned int BaseFramebuffer :: makeRenderbuffer(int width, int height)
{
    unsigned int renderbuffer;
    glGenRenderbuffers(1, &renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    return renderbuffer;
}



ColorFramebuffer::ColorFramebuffer(int width, int height, BaseTexture color_texture) : BaseFramebuffer(width, height), m_color_texture(-1), m_depth_renderbuffer(-1)
{
    use();
    m_color_texture = color_texture.create(width, height);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color_texture, 0);

    m_depth_renderbuffer = makeRenderbuffer(width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depth_renderbuffer);

    checkFramebuffer();
    unuse();
}

unsigned int ColorFramebuffer::getColorTexture()
{
    return m_color_texture;
}



ShadowFramebuffer::ShadowFramebuffer(int width, int height) : BaseFramebuffer(width, height), m_depth_texture(-1)
{
    use();
    m_depth_texture = BaseTexture().filters(GL_NEAREST, GL_NEAREST).formats(GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT).dataType(GL_FLOAT).wrap(GL_REPEAT, GL_REPEAT).create(width, height);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth_texture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    checkFramebuffer();
    unuse();
}

unsigned int ShadowFramebuffer::getDepthTexture()
{
    return m_depth_texture;
}



