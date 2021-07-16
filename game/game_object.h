#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../code/base_object.h"
#include "../code/base_program.h"
#include "../code/vertex_data.h"

using glm::vec3;
using glm::mat4;
using glm::value_ptr;

const int room_radius = 10;
const int room_size = 2 * room_radius;
const int wall_thickness = 1;
const int wall_height = 5;
const int door_radius = 2;
const int door_width = 2 * door_radius;
const int map_width = 10;
const int map_height = 10;

enum GameObjectType
{
    FLOOR,
    WALL_RIGHT,
    WALL_BACK,
    WALL_FRONT,
    WALL_LEFT,
    WALL_RIGHT_DOOR,
    WALL_BACK_DOOR,
    WALL_FRONT_DOOR,
    WALL_LEFT_DOOR,
};

class GameObject : public BaseObject
{
   mat4 m_mvp_matrix;
   vec3 m_middle;
public:
    GameObject(const vector<float>& data, const vector<unsigned int> vao_setup, vec3 middle);
    void drawAt(const vec3& position, BaseProgram& program, float scale = 1.f);
};


class GameObjectProperties
{
    vec3 m_position;
    GameObjectType m_type;
public:
    GameObjectProperties(int pos_x, int pos_y, GameObjectType type);
    GameObjectType getType();
    vec3& getPos();
};

class GameObjectManager
{
    vector<GameObject*> m_objects;
    void addObject(vector<float>& vertices, vec3 middle);
public:
    void drawObject(GameObjectProperties& data, BaseProgram& program);
    GameObjectManager();
    ~GameObjectManager();
};
#endif // GAME_OBJECT_H
