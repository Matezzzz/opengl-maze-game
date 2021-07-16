#include "game_object.h"
#include <iostream>
GameObject::GameObject(const vector<float>& data, const vector<unsigned int> vao_setup, vec3 middle) : BaseObject({data}, {vao_setup}), m_mvp_matrix(1.f), m_middle(middle)
{
}

void GameObject::drawAt(const vec3& position, BaseProgram& program, float scale)
{
    m_mvp_matrix = glm::translate(glm::scale(glm::mat4(1.f), vec3(scale, scale, scale)), position);
    program.uniMat4fv("model_matrix", m_mvp_matrix);
    program.uni3fv("middle", m_middle + position);
    BaseObject::Draw();
}


GameObjectManager::GameObjectManager() : m_objects()
{
    float room_r = room_radius - 0.1f;
    float room_b = room_r - wall_thickness + 0.1f;
    float room_d = door_radius;
    float room_t = room_radius;

    vector<float> floor_vertices = VertexData::fourPointsTo3D({vec2(-room_b, -room_b), vec2(-room_b, room_b),  vec2(room_b, -room_b), vec2(room_b, room_b)}, 0.5f);
    vector<float> wall_back_right_vertices  = VertexData::fourPointsTo3D({vec2(-room_b, -room_b), vec2(-room_r, -room_r), vec2(-room_b,  room_b), vec2(-room_r,  room_r)}, wall_height);
    vector<float> wall_back_left_vertices   = VertexData::fourPointsTo3D({vec2( room_b, -room_b), vec2( room_r, -room_r), vec2(-room_b, -room_b), vec2(-room_r, -room_r)}, wall_height);
    vector<float> wall_front_right_vertices = VertexData::fourPointsTo3D({vec2(-room_b,  room_b), vec2(-room_r,  room_r), vec2( room_b,  room_b), vec2( room_r,  room_r)}, wall_height);
    vector<float> wall_front_left_vertices  = VertexData::fourPointsTo3D({vec2( room_b,  room_b), vec2( room_r,  room_r), vec2( room_b, -room_b), vec2( room_r, -room_r)}, wall_height);

    vector<float> wall_back_right_door_vertices = VertexData::join(VertexData::join(
                                                                    VertexData::fourPointsTo3D({vec2(-room_b, -room_b), vec2(-room_r, -room_r), vec2{-room_b, -room_d}, vec2(-room_r, -room_d)}, wall_height),
                                                                    VertexData::fourPointsTo3D({vec2(-room_b,  room_d), vec2(-room_r,  room_d), vec2{-room_b,  room_b}, vec2(-room_r,  room_r)}, wall_height)),
                                                                    VertexData::fourPointsTo3D({vec2(-room_b, -room_d), vec2(-room_t, -room_d), vec2(-room_b,  room_d), vec2(-room_t,  room_d)}, 0.5f));
    vector<float> wall_back_left_door_vertices = VertexData::join(VertexData::join(
                                                                    VertexData::fourPointsTo3D({vec2( room_b, -room_b), vec2( room_r, -room_r), vec2{ room_d, -room_b}, vec2( room_d, -room_r)}, wall_height),
                                                                    VertexData::fourPointsTo3D({vec2(-room_d, -room_b), vec2(-room_d, -room_r), vec2{-room_b, -room_b}, vec2(-room_r, -room_r)}, wall_height)),
                                                                    VertexData::fourPointsTo3D({vec2( room_d, -room_b), vec2( room_d, -room_t), vec2(-room_d, -room_b), vec2(-room_d, -room_t)}, 0.5f));
    vector<float> wall_front_right_door_vertices = VertexData::join(VertexData::join(
                                                                    VertexData::fourPointsTo3D({vec2(-room_b,  room_b), vec2(-room_r,  room_r), vec2{-room_d,  room_b}, vec2(-room_d,  room_r)}, wall_height),
                                                                    VertexData::fourPointsTo3D({vec2( room_d,  room_b), vec2( room_d,  room_r), vec2{ room_b,  room_b}, vec2( room_r,  room_r)}, wall_height)),
                                                                    VertexData::fourPointsTo3D({vec2(-room_d,  room_b), vec2(-room_d,  room_t), vec2( room_d,  room_b), vec2( room_d,  room_t)}, 0.5f));
    vector<float> wall_front_left_door_vertices = VertexData::join(VertexData::join(
                                                                    VertexData::fourPointsTo3D({vec2{ room_b, -room_d}, vec2( room_r, -room_d), vec2( room_b, -room_b), vec2( room_r, -room_r)}, wall_height),
                                                                    VertexData::fourPointsTo3D({vec2{ room_b,  room_b}, vec2( room_r,  room_r), vec2( room_b,  room_d), vec2( room_r,  room_d)}, wall_height)),
                                                                    VertexData::fourPointsTo3D({vec2( room_b,  room_d), vec2( room_t,  room_d), vec2( room_b, -room_d), vec2( room_t, -room_d)}, 0.5f));//vertices, VAO, middle
    addObject(floor_vertices, {0.f, 0.f, 0.f});
    addObject(wall_back_right_vertices,     {-room_b, 0.f, 0.f});
    addObject(wall_back_left_vertices,      {0.f, -room_b, 0.f});
    addObject(wall_front_right_vertices,    {0.f,  room_b, 0.f});
    addObject(wall_front_left_vertices,     { room_b, 0.f, 0.f});
    addObject(wall_back_right_door_vertices,{-room_b, 0.f, 0.f});
    addObject(wall_back_left_door_vertices, {0.f, -room_b, 0.f});
    addObject(wall_front_right_door_vertices, {0.f, room_b, 0.f});
    addObject(wall_front_left_door_vertices, {room_b, 0.f, 0.f});
}

void GameObjectManager::addObject(vector<float>& vertices, vec3 middle)
{
    m_objects.push_back(new GameObject(vertices, {3, 3}, middle));
}

void GameObjectManager::drawObject(GameObjectProperties& data, BaseProgram& program)
{
    m_objects[data.getType()] -> drawAt(data.getPos(), program);
}

GameObjectManager::~GameObjectManager()
{
    for (GameObject* obj : m_objects)
    {
        delete obj;
    }
}

GameObjectProperties::GameObjectProperties(int pos_x, int pos_y, GameObjectType type) : m_position(vec3(pos_x, pos_y, 0.f)), m_type(type)
{
}

GameObjectType GameObjectProperties::getType()
{
    return m_type;
}

vec3& GameObjectProperties::getPos()
{
    return m_position;
}
