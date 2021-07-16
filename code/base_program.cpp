#include "base_program.h"

BaseProgram::BaseProgram(string directory) : BaseProgram(directory + "/vertex.glsl", directory + "/fragment.glsl")
{
}


BaseProgram::BaseProgram(string vertex, string fragment) : m_program_id(-1)
{
    m_program_id = glCreateProgram();

    ProgramPart vertex_shader(GL_VERTEX_SHADER, vertex);
    vertex_shader.attach(m_program_id);

    ProgramPart fragment_shader(GL_FRAGMENT_SHADER, fragment);
    fragment_shader.attach(m_program_id);

    glLinkProgram(m_program_id);

    int link_result;
    glGetProgramiv(m_program_id, GL_LINK_STATUS, &link_result);
    if (!link_result)
    {
        char program_info_log[512];
        glGetProgramInfoLog(m_program_id, 512, NULL, program_info_log);
        cout << "Linking program failed. Error:\n" << program_info_log << "\n";
    }
    vertex_shader.detach(m_program_id);
    fragment_shader.detach(m_program_id);
}


BaseProgram::BaseProgram(string vertex, string fragment, string geometry) : m_program_id(glCreateProgram())
{
    //m_program_id = glCreateProgram();

    ProgramPart vertex_shader(GL_VERTEX_SHADER, vertex);
    vertex_shader.attach(m_program_id);

    ProgramPart fragment_shader(GL_FRAGMENT_SHADER, fragment);
    fragment_shader.attach(m_program_id);

    ProgramPart geometry_shader(GL_GEOMETRY_SHADER, geometry);
    geometry_shader.attach(m_program_id);

    glLinkProgram(m_program_id);

    int link_result;
    glGetProgramiv(m_program_id, GL_LINK_STATUS, &link_result);
    if (!link_result)
    {
        char program_info_log[512];
        glGetProgramInfoLog(m_program_id, 512, NULL, program_info_log);
        cout << "Linking program failed. Error:\n" << program_info_log << "\n";
    }
    vertex_shader.detach(m_program_id);
    fragment_shader.detach(m_program_id);
    geometry_shader.detach(m_program_id);
}

void BaseProgram::use()
{
    glUseProgram(m_program_id);
}

void BaseProgram::uniMat4fv(string name, mat4& matrix)
{
    use();
    glUniformMatrix4fv(uniLoc(name), 1, false, value_ptr(matrix));
}

void BaseProgram::uni1i(string name, int x)
{
    use();
    glUniform1i(uniLoc(name), x);
}

void BaseProgram::uni1f(string name, float x)
{
    use();
    glUniform1f(uniLoc(name), x);
}

void BaseProgram::uni3f(string name, float x, float y, float z)
{
    use();
    glUniform3f(uniLoc(name), x, y, z);
}

void BaseProgram::uni3fv(string name, const vec3& vec)
{
    use();
    glUniform3fv(uniLoc(name), 1, value_ptr(vec));
}

unsigned int BaseProgram::uniLoc(string name)
{
    return glGetUniformLocation(m_program_id, name.c_str());
}



ProgramPart::ProgramPart(unsigned int shader_type, string filename) : m_shader_id(glCreateShader(shader_type))
{
    string code;
    ifstream file(filename);
    if (file)
    {
        string line;
        while (getline(file, line))
        {
            code += line + "\n";
        }
        file.close();
        //m_shader_id = glCreateShader(shader_type);
        const char* code_pointer = code.c_str();
        glShaderSource(m_shader_id, 1, &code_pointer, NULL);
        glCompileShader(m_shader_id);
        int compile_result;
        glGetShaderiv(m_shader_id, GL_COMPILE_STATUS, &compile_result);
        if (!compile_result)
        {
            char shader_info_log[512];
            glGetShaderInfoLog(m_shader_id, 512, NULL, shader_info_log);
            cout << "compiling " << filename << " failed. Errors:\n" << shader_info_log << "\n";
        }
    }
    else
    {
        cout << "Cannot open shader: " << filename << "\n";
    }
}

void ProgramPart::attach(unsigned int program_id)
{
    glAttachShader(program_id, m_shader_id);
}

void ProgramPart::detach(unsigned int program_id)
{
    glDetachShader(program_id, m_shader_id);
}

ProgramPart::~ProgramPart()
{
    glDeleteShader(m_shader_id);
}
