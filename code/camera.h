#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "timer.h"

class Camera
{
    glm::vec3 m_position;
    glm::vec3 m_direction;
    glm::vec3 m_up;


    Timer* m_timer;

    const int m_key_forward  = GLFW_KEY_UP;
    const int m_key_backward = GLFW_KEY_DOWN;
    const int m_key_right    = GLFW_KEY_RIGHT;
    const int m_key_left     = GLFW_KEY_LEFT;

    const float m_speed = 10.f;
public:
    glm::mat4 view_matrix;

    Camera(glm::vec3 position, glm::vec3 look_at, Timer* timer);
    void update(GLFWwindow*& window);
};
