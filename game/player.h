#ifndef PLAYER_H
#define PLAYER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../code/base_program.h"
#include "game_object.h"
#include "game_room.h"
#include "../code/vertex_data.h"

using glm::vec3;
using glm::mat4;

const float player_speed = 0.01;

class Player : public GameObject
{
    vec3 m_position;
    vec3 m_velocity;
    mat4 m_mvp_matrix;
    float m_side_radius = 0.5f;
    bool checkCollisions(GameRoomManager& rooms);
public:
    Player(float x, float y);
    void update(GLFWwindow* window, GameRoomManager& game_room);
    void draw(BaseProgram& program);
    bool hasWon();
    vec3& getPos();
};
#endif // PLAYER_H
