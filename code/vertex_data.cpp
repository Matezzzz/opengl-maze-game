#include "vertex_data.h"
#include <iostream>
using std::cout;

vector<float> VertexData::from8Points(vector<vec3> points, bool make_normals)
{
    assert(points.size() == 8 && "You have to supply 8 points. Come on, the function is even named like that.");

    vector<ivec4> quads_indices = {ivec4(0,1,3,2), ivec4(1,5,7,3), ivec4(2,3,7,6), ivec4(6,7,5,4), ivec4(4,0,2,6), ivec4(5,1,0,4)};
    vector<ivec3> quad_to_triangle_indices = {ivec3(2,0,1), ivec3(0,2,3)};
    vector<float> result(6 * 6 * (make_normals ? 6 : 3));
    int current_result_index = 0;
    for (ivec4 quad_ind : quads_indices)
    {
        vector<vec3> quad(4);
        for (int i = 0; i < 4; i++)
        {
            quad[i] = points[quad_ind[i]];
        }
        for (int i = 0; i < 2; i++)
        {
            vector<vec3> triangle(3);
            for (int j = 0; j < 3; j++)
            {
                triangle[j] = quad[quad_to_triangle_indices[i][j]];
            }
            vec3 normal = cross(triangle[1] - triangle[0], triangle[2] - triangle[0]);
            for (int j = 0; j < 3; j++)
            {
                result[current_result_index++] = triangle[j].x;
                result[current_result_index++] = triangle[j].y;
                result[current_result_index++] = triangle[j].z;
                if (make_normals)
                {
                    result[current_result_index++] = normal.x;
                    result[current_result_index++] = normal.y;
                    result[current_result_index++] = normal.z;
                }
            }
        }
    }
    return result;
}

vector<float> VertexData::makeCube(int a, bool make_normals)
{
    vector<vec3> points(8);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                points[4 * i + 2 * j + k] = vec3(a*(i - 0.5f), a*(j - 0.5f), a*(k - 0.5f));
            }
        }
    }
    return VertexData::from8Points(points, make_normals);
}

vector<float> VertexData::makeQuad(vector<vec3> points, bool make_normals)
{
    assert(points.size() == 4 && "You need 4 points to make a quad. Learn to count. :')");
    vector<float> result(6 * (make_normals ? 6 : 3));
    int current_result_index = 0;
    vector<ivec3> quad_to_triangle_indices = {ivec3(2,0,1), ivec3(0,2,3)};
    for (int i = 0; i < 2; i++)
    {
        vector<vec3> triangle(3);
        for (int j = 0; j < 3; j++)
        {
            triangle[j] = points[quad_to_triangle_indices[i][j]];
        }
        vec3 normal = cross(triangle[1] - triangle[0], triangle[2] - triangle[0]);
        for (int j = 0; j < 3; j++)
        {
            result[current_result_index++] = triangle[j].x;
            result[current_result_index++] = triangle[j].y;
            result[current_result_index++] = triangle[j].z;
            if (make_normals)
            {
                result[current_result_index++] = normal.x;
                result[current_result_index++] = normal.y;
                result[current_result_index++] = normal.z;
            }
        }
    }
    return result;
}

vector<vec3> VertexData::addZCoordinate(vector<vec2> points, float default_value)
{
    vector<vec3> result(points.size());
    for (unsigned int i = 0; i < points.size(); i++)
    {
        result[i] = vec3(points[i].x, points[i].y, default_value);
    }
    return result;
}

vector<vec3> VertexData::extrudeZ(vector<vec3> data, float dist)
{
    vector<vec3> result(data.size() * 2);
    for (unsigned int i = 0; i < data.size() * 2; i++)
    {
        result[i] = data[i % data.size()];
    }
    for (unsigned int i = 0; i < data.size(); i++)
    {
        result[data.size() + i].z += dist;
    }
    return result;
}

vector<float> VertexData::fourPointsTo3D(vector<vec2> points, float height)
{
    return VertexData::from8Points(VertexData::extrudeZ(VertexData::addZCoordinate(points), height));
}

vector<float> VertexData::join(vector<float> data1, vector<float> data2)
{
    vector<float> result(data1.size() + data2.size());
    for (unsigned int i = 0; i < data1.size(); i++)
    {
        result[i] = data1[i];
    }
    for (unsigned int i = data1.size(); i < data1.size() + data2.size(); i++)
    {
        result[i] = data2[i - data1.size()];
    }
    return result;
}
