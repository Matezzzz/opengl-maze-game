#ifndef BUFFER_H
#define BUFFER_H

#include "glad.h"
#include <vector>

using std::vector;

class Buffer
{
    unsigned int m_buffer;
public:
    Buffer();
    void UpdateData(vector<float> data, int usage = GL_STATIC_DRAW, int target = GL_ARRAY_BUFFER);
    void UpdateData(vector<int> data, int usage = GL_STATIC_DRAW, int target = GL_ARRAY_BUFFER);
    void Bind  (int target = GL_ARRAY_BUFFER);
    void Unbind(int target = GL_ARRAY_BUFFER);
    void FloatToVAO(vector<unsigned int> setup, int& current_index);
    ~Buffer();
};
#endif // BUFFER_H
