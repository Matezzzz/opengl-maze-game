#ifndef BASE_PROGRAM_H
#define BASE_PROGRAM_H

#include "glad.h"
#include <fstream>
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using std::string;
using std::cout;
using std::ifstream;
using glm::vec3;
using glm::mat4;
using glm::value_ptr;

class BaseProgram
{
private:
    unsigned int m_program_id;
public:
    BaseProgram(string directory);  //opens vertex.glsl and fragment.glsl in target directory
    BaseProgram(string vertex, string fragment);
    BaseProgram(string vertex, string fragment, string geometry);
    void use();
    void uniMat4fv(string name, mat4& matrix);
    void uni1i(string name, int x);
    void uni1f(string name, float x);
    void uni3f(string name, float x, float y, float z);
    void uni3fv(string name, const vec3& vec);
    unsigned int uniLoc(string name);
};

class ProgramPart
{
public:
    unsigned int m_shader_id;
    ProgramPart(unsigned int shader_type, string filename);
    void attach(unsigned int program_id);
    void detach(unsigned int program_id);
    ~ProgramPart();
};
#endif // BASE_PROGRAM_H
