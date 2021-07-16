#include "camera.h"

GameCamera::GameCamera(vec3 player_pos, vec3 offset) : m_center_position(player_pos), m_velocity(0.f, 0.f, 0.f), m_offset(offset), m_view_matrix(1.f)
{
}

void GameCamera::update(const vec3& player_pos)
{
    m_velocity += (player_pos - m_center_position) * 0.01f;
    m_center_position += m_velocity;
    m_velocity *= 0.9;
    m_view_matrix = glm::lookAt(m_center_position + m_offset, (4.f * m_center_position + player_pos) / 5.f, {0.f, 0.f, 1.f});
}

mat4& GameCamera::getViewMatrix()
{
    return m_view_matrix;
}

const vec3 GameCamera::getPos()
{
    return m_center_position + m_offset;
}
