#include "player.h"


Player::Player(float pos_x, float pos_y) : GameObject(VertexData::makeCube(1), {3, 3}, {0.f, 0.f, 0.f}), m_position(pos_x, pos_y, 1.f), m_velocity(0.f, 0.f, 0.f), m_mvp_matrix(1.f)
{}

void Player::update(GLFWwindow* window, GameRoomManager& rooms)
{
    if (glfwGetKey(window, GLFW_KEY_LEFT))
    {
        m_velocity.x -= player_speed;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT))
    {
        m_velocity.x += player_speed;
    }
    if (glfwGetKey(window, GLFW_KEY_UP))
    {
        m_velocity.y += player_speed;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN))
    {
        m_velocity.y -= player_speed;
    }
    m_position.x += m_velocity.x;
    if (checkCollisions(rooms))
    {
        m_position.x -= m_velocity.x;
        m_velocity.x = 0;
    }
    m_position.y += m_velocity.y;
    if (checkCollisions(rooms))
    {
        m_position.y -= m_velocity.y;
        m_velocity.y = 0;
    }
    m_velocity *= 0.95;
}

void Player::draw(BaseProgram& base_program)
{
    GameObject::drawAt(m_position, base_program, 1.f);
}

bool Player::hasWon()
{
    return (static_cast<int>(m_position.x / room_size) == map_width - 1 && static_cast<int>(m_position.y / room_size) == map_height - 1);
}

vec3& Player::getPos()
{
    return m_position;
}

bool Player::checkCollisions(GameRoomManager& rooms)
{
    return (rooms.doesCollide(m_position + vec3(-m_side_radius, -m_side_radius, 0.f))
         || rooms.doesCollide(m_position + vec3(-m_side_radius,  m_side_radius, 0.f))
         || rooms.doesCollide(m_position + vec3( m_side_radius, -m_side_radius, 0.f))
         || rooms.doesCollide(m_position + vec3( m_side_radius,  m_side_radius, 0.f)));
}
