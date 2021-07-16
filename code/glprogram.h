#ifndef GLPROGRAM_H
#define GLPROGRAM_H

#include <string>
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>
#include "utils.h"

using std::string;
using std::to_string;
using std::ios;
using std::ifstream;
using std::cout;
using std::endl;


class GLProgram          //class managing the basics around openGL program objects
{
public:
     void setProgram(unsigned int GLProgramID);     //creates GLProgram from previously made GL Program
    bool loadFromShaders(const char* vertex_shader_path, const char* fragment_shader_path);     //creates GLProgram from vertex and fragment shader
    bool loadFromShaders(const char* vertex_shader_path, const char* fragment_shader_path, const char* geometry_shader_path);
    void use();             //use assigned program for rendering and setting uniforms
    void destroy();


    void uni1i(const char* name, int x);

    void uni1f(const char* name, float x);
    void uni2f(const char* name, float x, float y);
    void uni3f(const char* name, float x, float y, float z);

    void unifarray(const char* name, float* values, int valueCount);

	void univec2array(const char* name, glm::vec2* values, int valueCount);
    void unimat4fv(const char* name, float* value);

    unsigned int getProgram();
private:
    unsigned int programID;     //GL program ID
    unsigned int* shaderIDs;   //ID's of attached programs, first number is current index

    void setupProgram(int shader_count);
    bool attachFileToProgram(const char* shader_path, const int shader_type);       //attach compiled shader file to current program
    bool linkProgram();         //link GL Program
    unsigned int uniLoc(const char* name);      //get uniform location from shader
};
#endif // GLPROGRAM_H
