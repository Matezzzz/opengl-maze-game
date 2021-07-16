#include "font.h"

Font::Font(string filename, int font_size, mat4& projectionM) : m_font_size(font_size), m_letters(), m_glyph({vector<float>(4 * 6, 0)}, {{4}}, {GL_DYNAMIC_DRAW}), m_program("shaders/font")
{
    FT_Library ft_lib;
    if (FT_Init_FreeType(&ft_lib))
        cout << "FreeType initialization error.";

    FT_Face face;
    if (FT_New_Face(ft_lib, filename.c_str(), 0, &face))
        cout << "Cannot load font.";
    FT_Set_Pixel_Sizes(face, 0, font_size);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char cur = 0; cur < 128; cur++)
    {
        if (FT_Load_Char(face, cur, FT_LOAD_RENDER))
        {
            cout << "cannot load glyph " << cur << "\n";
            continue;
        }

        unsigned int tex;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
                     face -> glyph -> bitmap.width,
                     face -> glyph -> bitmap.rows,
                     0, GL_RED, GL_UNSIGNED_BYTE,
                     face -> glyph -> bitmap.buffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {tex,
                               ivec2(face -> glyph -> bitmap.width, face -> glyph -> bitmap.rows),
                               ivec2(face -> glyph -> bitmap_left, face -> glyph -> bitmap_top),
                               static_cast<unsigned int>(face -> glyph -> advance.x)};

        m_letters.insert(pair<char, Character>(cur, character));
    }
    FT_Done_Face(face);
    FT_Done_FreeType(ft_lib);

    m_program.use();
    m_program.uniMat4fv("MVP", projectionM);
}

void Font::drawText(string text, float x, float y, float scale, vec3 color)
{
    m_program.use();
    m_program.uni3f("text_color", color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = m_letters[*c];

        float pos_x = x + ch.g_bearing.x * scale;
        float pos_y = y - (ch.g_size.y - ch.g_bearing.y) * scale;

        float w = ch.g_size.x * scale;
        float h = ch.g_size.y * scale;
        vector<float> vertices = {
             pos_x,     pos_y + h,   0.0, 0.0,
             pos_x,     pos_y,       0.0, 1.0,
             pos_x + w, pos_y,       1.0, 1.0,

             pos_x,     pos_y + h,   0.0, 0.0,
             pos_x + w, pos_y,       1.0, 1.0,
             pos_x + w, pos_y + h,   1.0, 0.0
        };
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        m_glyph.UpdateData({vertices});
        m_glyph.Draw();
        x += (ch.advance >> 6) * scale;
    }
}

int Font::getSize()
{
    return m_font_size;
}
