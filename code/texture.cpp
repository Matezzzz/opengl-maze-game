#include "texture.h"
#include <iostream>
#include "stb_image.h"


BaseTexture& BaseTexture::filters(GLenum minf, GLenum magf)
{
    min_filter = minf;
    mag_filter = magf;
    return *this;
}

BaseTexture& BaseTexture::formats(GLenum internal, GLenum normal)
{
    internal_format = internal;
    format = normal;
    return *this;
}

BaseTexture& BaseTexture::wrap(GLenum w_s, GLenum w_t)
{
    wrap_s = w_s;
    wrap_t = w_t;
    return *this;
}

BaseTexture& BaseTexture::dataType(unsigned type)
{
    data_type = type;
    return *this;
}

unsigned int BaseTexture::create(int width, int height)
{
    unsigned int texture = newTexture(nullptr, width, height);
    setParameters(texture);
    return texture;
}

unsigned int BaseTexture::loadFromFile(std::string filename, bool flip_on_load)
{
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(flip_on_load);
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 03);
    unsigned int texture = newTexture(data, width, height);
    setParameters(texture);
    return texture;
}

unsigned int BaseTexture::newTexture(void* data, int width, int height)
{
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, data_type, data);
    return texture;
}

void BaseTexture::setParameters(unsigned int texture)
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,  min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
    glBindTexture(GL_TEXTURE_2D, 0);
}


