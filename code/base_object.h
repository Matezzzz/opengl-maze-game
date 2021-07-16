#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include <vector>
#include <initializer_list>
#include "buffer.h"

using std::vector;
using std::initializer_list;

class BaseObject
{
    vector<Buffer> m_buffers;
    vector<int> m_buffers_usage;
    unsigned int m_VAO;
    int vertex_count = -1;
    int render_type = GL_TRIANGLES;
public:
    BaseObject(const vector<vector<float>>& data, const vector<vector<unsigned int>> vao_setup, const vector<int> buffer_usage = {});
    void Draw();
    void UpdateData(vector<vector<float>> data);
    void SetRenderType(int type);
    ~BaseObject();
};
#endif // BASE_OBJECT_H
