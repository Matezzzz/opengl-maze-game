#include "camera.h"
#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 direction, Timer* timer) : m_position(position), m_direction(direction), m_up(0.f, 0.f, 1.f), m_timer(timer), view_matrix(glm::lookAt(m_position, m_position + direction, m_up))
{
}

void Camera::update(GLFWwindow*& window)
{
    glm::vec3 next_move(0.f);
    if (glfwGetKey(window, m_key_forward))
    {
        next_move += m_timer -> frame() * m_speed * glm::normalize(m_direction);
    }
    if (glfwGetKey(window, m_key_backward))
    {
        next_move -= m_timer -> frame() * m_speed * glm::normalize(m_direction);
    }
    if (glfwGetKey(window, m_key_right))
    {
        next_move += m_timer -> frame() * m_speed * glm::normalize(glm::cross(m_direction, m_up));
    }
    if (glfwGetKey(window, m_key_left))
    {
        next_move -= m_timer -> frame() * m_speed * glm::normalize(glm::cross(m_direction, m_up));
    }
    if (next_move.x != 0 || next_move.y != 0 || next_move.z != 0)
    {
        m_position += next_move;
        view_matrix = glm::lookAt(m_position, m_position + m_direction, m_up);
    }
}

