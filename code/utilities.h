#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <cassert>
#include <glad/glad.h>

using std::string;


class GLUtilities
{
public:
    static void makeScreenshot(string filename, int screen_width, int screen_height);
};
#endif // UTILITIES_H
