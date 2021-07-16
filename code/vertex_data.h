#ifndef VERTEX_DATA_H
#define VERTEX_DATA_H

#include <vector>
#include <cassert>
#include <glm/glm.hpp>

using glm::vec2;
using glm::vec3;
using glm::ivec3;
using glm::ivec4;
using glm::cross;
using std::vector;

class VertexData
{
public:
    static vector<float> from8Points(vector<vec3> points, bool make_normals = true);
    static vector<float> makeCube(int a = 1, bool make_normals = true);
    static vector<float> makeQuad(vector<vec3> points, bool make_normals = true);
    static vector<vec3> addZCoordinate(vector<vec2> points, float default_value = 0.f);
    static vector<vec3> extrudeZ(vector<vec3> data, float dist);
    static vector<float> join(vector<float> data1, vector<float> data2);
    static vector<float> fourPointsTo3D(vector<vec2> points, float height);
};

#endif // VERTEX_DATA_H
