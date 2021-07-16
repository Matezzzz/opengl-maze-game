#ifndef UTILS_H
#define UTILS_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"

using namespace std;


std::string readFile(const char* filename);
void checkErrors();
void cleanErrors();
template < typename T > std::string to_string( const T& n );
float clamp(float* number, float from, float to);
unsigned int createGLProgram(char const* vertex_file, char const* fragment_file, char const* geometry_file);
unsigned int TextureFromFile(const char* path, const string& directory);
#endif
