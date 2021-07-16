#include "buffer.h"

Buffer::Buffer() : m_buffer(-1)
{
    glGenBuffers(1, &m_buffer);
}

void Buffer::UpdateData(vector<float> data, int usage, int target)
{
    Bind(target);
    glBufferData(target, data.size() * sizeof(float), &data[0], usage);
    Unbind(target);
}

void Buffer::UpdateData(vector<int> data, int usage, int target)
{
    Bind(target);
    glBufferData(target, data.size() * sizeof(int), &data[0], usage);
    Unbind(target);
}

void Buffer::Bind(int target)
{
    glBindBuffer(target, m_buffer);
}

void Buffer::Unbind(int target)
{
    glBindBuffer(target, 0);
}

void Buffer::FloatToVAO(vector<unsigned int> setup, int& current_index)
{
    int stride = 0;
    for (unsigned int i : setup)
        stride += i;
    stride *= sizeof(float);
    int offset = 0;
    Bind();
    for (unsigned int i : setup)
    {
        glVertexAttribPointer(current_index, i, GL_FLOAT, GL_FALSE, stride, (void*)(offset * sizeof(float)));
        glEnableVertexAttribArray(current_index++);
        offset += i;
    }
    Unbind();
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &m_buffer);
}
