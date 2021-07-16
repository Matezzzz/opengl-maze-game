#ifndef BASE_TEXTURE_H
#define BASE_TEXTURE_H

#include "glad.h"
#include <string>

class BaseTexture
{
	int min_filter = GL_LINEAR;
	int mag_filter = GL_LINEAR;
	int wrap_s = GL_REPEAT;
	int wrap_t = GL_REPEAT;

	int internal_format = GL_RGB;
    int format = GL_RGB;

    unsigned int data_type = GL_UNSIGNED_BYTE;
public:
	BaseTexture& filters(GLenum minf, GLenum magf);
	BaseTexture& formats(GLenum internal, GLenum normal);
	BaseTexture& wrap(GLenum w_s, GLenum w_t);
	BaseTexture& dataType(unsigned int type);
    unsigned int create(int width, int height);
    unsigned int loadFromFile(std::string filename, bool flip_on_load = false);
private:
    void setParameters(unsigned int texture);
    unsigned int newTexture(void* data, int width, int height);
};
#endif // BASE_TEXTURE_H
