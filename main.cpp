
#include "code/glad.h"
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "code/stb_image.h"
#undef STB_IMAGE_IMPLEMENTATION

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <sstream>
#include <math.h>
#include <vector>
#include <deque>
#include <random>
#include <ctime>
#include <fstream>


#define PI 3.14159265358979323846

#include "code/utilities.h"
#include "code/base_program.h"
#include "code/utils.h"
#include "code/timer.h"
#include "code/base_object.h"
#include "code/base_framebuffer.h"
#include "code/random.h"
#include "code/font.h"
#include "code/vertex_data.h"
#include "game/game_room.h"
#include "game/player.h"
#include "game/camera.h"


using glm::vec3;

GLFWwindow* window;

// window width, height and title
const string window_title = "Maze";

const int screen_width = 1024;
const int screen_height = 1024;

const float screen_ratio = 1.0 * screen_width / screen_height;


bool init_libraries()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(screen_width, screen_height, window_title.c_str(), NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return false;
    }
    return true;
}


void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


bool initialize()
{
    if (!init_libraries())
    {
        cout << "Libraries initialization error." << endl;
        return false;
    }
    glViewport(0, 0, screen_width, screen_height);
    glClearColor(0.f, 0.f, 0.f, 1.0f);

    return true;
}

class Mouse
{
    double pos_x = 0.0;
    double pos_y = 0.0;
    bool pressed = false;
public:
    void update()
    {
        glfwGetCursorPos(window, &pos_x, &pos_y);
        pressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    }
    double getX()
    {
        return pos_x;
    }
    double getY()
    {
        return pos_y;
    }
    bool getPressed()
    {
        return pressed;
    }
};


int main()
{
    if (!initialize())
    {
        cout << "Error happened." << endl;
        return -1;
    }
    glClearColor(0.8, 0.8, 0.8, 1.0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    Random random;
    Mouse mouse;
    Timer timer;
    GameObjectManager object_manager;
    GameRoomManager rooms(&object_manager, &random);
    Player player(0.f, 0.f);
    GameCamera camera(player.getPos(), {-1.5f, -9.f, 37.5f});
    ShadowFramebuffer shadow_framebuffer(2048, 2048);


    BaseProgram shadow_program("shaders/shadow");

    glm::mat4 projection_matrix = glm::perspective(45.f, screen_ratio, 0.1f, 100.f);
    glm::mat4 light_projection_matix = glm::ortho(-30.f, 30.f, -30.f, 30.f, 1.f, 100.f);
    glm::mat4 light_projection_view_matrix;
    vec3 light_position(6.f, 6.f, 20.f);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    BaseProgram object_program("shaders/game_object");
    object_program.uni3f("material.diffuse", .5f, .5f, .5f);
    object_program.uni3f("material.specular", .75f, .75f, .75f);
    object_program.uni3fv("light.direction", -light_position);
    object_program.uni3f("light.color", .5f, .5f, .5f);
    object_program.uni1i("shadow_map", 0);

    glm::mat4 projection_view_matrix;
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        mouse.update();

        player.update(window, rooms);
        camera.update(player.getPos());
        rooms.update(player.getPos());

        projection_view_matrix = projection_matrix * camera.getViewMatrix();
        light_projection_view_matrix = light_projection_matix * glm::lookAt(player.getPos() + light_position, player.getPos(), vec3(0.f, 0.f, 1.f));

        object_program.uniMat4fv("view_projection_matrix", projection_view_matrix);
        object_program.uniMat4fv("light_matrix", light_projection_view_matrix);
        object_program.uni3fv("player_position", player.getPos());
        object_program.uni3fv("camera_position", camera.getPos());

        shadow_program.uniMat4fv("light_matrix", light_projection_view_matrix);
        shadow_program.uni3fv("player_position", player.getPos());

        shadow_framebuffer.use();
        shadow_framebuffer.setViewport();
        glClear(GL_DEPTH_BUFFER_BIT);
        shadow_program.use();
        rooms.draw(shadow_program);
        player.draw(shadow_program);
        shadow_framebuffer.unuse();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, shadow_framebuffer.getDepthTexture());
        glViewport(0, 0, screen_width, screen_height);

        object_program.uni3f("material.ambient", .5f, .5f, .5f);
        object_program.uni1f("material.shininess", 10);
        rooms.draw(object_program);
        object_program.uni3f("material.ambient", .55f, .5f, .5f);
        object_program.uni1f("material.shininess", 512);
        player.draw(object_program);

        if (player.hasWon())
        {
            glfwTerminate();
            cout << "You have won\n";
            Timer::sleep(10);
            return 0;
        }

        timer.update();
        timer.makeFrameRate(60);

        //checkErrors();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
