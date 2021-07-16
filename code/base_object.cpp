#include "base_object.h"
#include "glad.h"
#include <cassert>
#include <iostream>

using std::cout;

BaseObject::BaseObject(const vector<vector<float>>& data, const vector<vector<unsigned int>> vao_setup, const vector<int> buffer_usage) : m_buffers(data.size()), m_buffers_usage((buffer_usage.size()) ? buffer_usage : vector<int>(data.size(), GL_STATIC_DRAW)), m_VAO(-1)
{
    assert(data.size() == vao_setup.size() && "There has to be same amount of data as VAO uses.");
    assert(data.size() == m_buffers_usage.size() && "There has to be same amount of data as usage information.");

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    int index = 0;

    for (const vector<float>& data_part : data)
    {
        int att_count = 0;
        for (int x : vao_setup.begin()[index])
            att_count += x;

        int current_vertex_count = data_part.size() / att_count;
        assert((current_vertex_count == vertex_count || vertex_count < 0) && "Invalid combination of data and vao setup.");
        vertex_count = current_vertex_count;
        m_buffers[index].UpdateData(data_part, m_buffers_usage[index]);
        m_buffers[index].FloatToVAO(vao_setup.begin()[index], index);
    }
}

void BaseObject::UpdateData(vector<vector<float>> data)
{
    assert(data.size() == m_buffers.size() && "There has to be same amount of data as buffers.");
    int index = 0;
    for (const vector<float>& data_part : data)
    {
        m_buffers[index].UpdateData(data_part, m_buffers_usage[index]);
        index++;
    }
}

void BaseObject::Draw()
{
    glBindVertexArray(m_VAO);
    glDrawArrays(render_type, 0, vertex_count);
    glBindVertexArray(0);
}

void BaseObject::SetRenderType(int type)
{
    render_type = type;
}

BaseObject::~BaseObject()
{
    glDeleteVertexArrays(1, &m_VAO);
}

