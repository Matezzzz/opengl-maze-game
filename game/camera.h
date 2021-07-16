#ifndef GAME_CAMERA_H
#define GAME_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using glm::vec3;
using glm::mat4;


class GameCamera
{
    vec3 m_center_position;
    vec3 m_velocity;
    vec3 m_offset;
    mat4 m_view_matrix;
public:
    GameCamera(vec3 position, vec3 offset_from_player);
    void update(const vec3& player_pos);
    const vec3 getPos();
    mat4& getViewMatrix();
};
#endif // GAME_CAMERA_H
