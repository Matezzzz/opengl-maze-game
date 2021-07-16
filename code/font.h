#ifndef FONT_H
#define FONT_H

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include "base_object.h"
#include "my_own/old/glprogram.h"

#include <map>
#include <string>
#include <iostream>


using std::string;
using std::map;
using std::cout;
using std::pair;
using std::pair;
using glm::ivec2;
using glm::vec3;
using glm::mat4;

struct Character
{
    unsigned int TextureID;
    ivec2 g_size;
    ivec2 g_bearing;
    unsigned int advance;
};


class Font
{
public:
    Font(string name, int font_size, mat4& projectionM);
    void drawText(string text, float x, float y, float scale, vec3 color);
    int getSize();
private:
    int m_font_size;
    map<char, Character> m_letters;
    BaseObject m_glyph;
    BaseProgram m_program;
};

#endif // FONT_H
