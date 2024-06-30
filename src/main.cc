#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "classes/object.h"
#include "classes/object_shapes.h"
#include "classes/object_handler.h"
#include "classes/settings.h"

int width = Settings::GetInstance().screen_.width;
int height = Settings::GetInstance().screen_.height;
bool fullscreen = Settings::GetInstance().screen_.fullscreen;
bool vsync = Settings::GetInstance().screen_.vsync;

float koef_screen = static_cast<float>(width) / height;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    // GLFW
    if (!glfwInit()) {
        std::cerr << "glfwInit error" << std::endl;
        return -1;
    }

    // OpenGL (3.1)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    GLFWwindow* window;
    if (fullscreen) {
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        window = glfwCreateWindow(mode->width, mode->height, "Hello, OpenGL!", monitor, nullptr);
    }
    else {
        window = glfwCreateWindow(width, height, "Hello, OpenGL!", nullptr, nullptr);
    }

    if (!window) {
        std::cerr << "glfwCreateWindow error" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Glad" << std::endl;
        glfwTerminate();
        return -1;
    }

    glScalef(1 / koef_screen, 1, 1);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(vsync);

#define CASE1

#ifdef CASE1

    Settings::GetInstance().world_parameters_.gravity = 0.0f;
    Rectangle rect(0, 0, 0, 2.0, 0.15);
    Circle circle0(0, 0.0, 3.5, 0.15);
    Circle circle1(0, -0.5, -0.2, 0.1);
    Circle circle2(0, -0.5, 0.2, 0.1);
    Circle circle3(0, 0.5, -0.2, 0.1);
    circle0.SetVelocity(glm::vec2(0.5f, -3.0f));
    rect.SetAngularVelocity(0.2);

#endif // CASE1
         
#ifdef CASE2

    Settings::GetInstance().world_parameters_.gravity = 0.0f;
    Settings::GetInstance().world_parameters_.restitution = 1.0f;
    Rectangle floor(1, -2, 0, 0.6f, 2.0f);
    Rectangle floor1(1, 2, 0, 0.6f, 2.0f);
    Rectangle floor2(1, 0, 1.2, 4.0f, 0.6f);
    Rectangle floor3(1, 0, -1.2, 4.0f, 0.6f);
    Circle circle0(0, 0, 0, 0.15);    
    Circle circle1(0, -0.5, -0.2, 0.3);
    Circle circle2(0, -0.5, 0.2, 0.15);
    Circle circle3(0, 0.5, -0.2, 0.15);
    Circle circle4(0, -0.1, -0.7, 0.1);
    Circle circle5(0, -0.8, 0.3, 0.15);
    Circle circle6(0, 0.2, -0.1, 0.1);
    circle0.SetVelocity(glm::vec2(3.5f, -1.2f));
    circle2.SetVelocity(glm::vec2(-3.0f, 1.2f));

#endif // CASE2

#ifdef CASE3

    Rectangle floor(1, 0, -5.8f, 10.0f, 11.0f);
    Circle circle0(0, -3, 0.7, 0.4);
    Circle circle1(0, -0.5, 0.3, 0.3);
    Circle circle2(0, 0.7, 0.5, 0.2);
    Circle circle3(0, 1.7, 0.2, 0.1);
    circle0.SetAngularVelocity(-5.0);
    circle2.SetAngularVelocity(4.0);
    circle1.SetVelocity(glm::vec2(0.0, 0));
    circle3.SetAngularVelocity(8.0);

#endif // CASE3

    int fps_counter = 0;

    float last_time = static_cast<float>(glfwGetTime());

    while (!glfwWindowShouldClose(window)) {        

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float current_time = static_cast<float>(glfwGetTime());
        float delta_time = current_time - last_time;
        ObjectHandler::GetInstance().MainCycle(Object::GetObjectsList(), delta_time);

        glfwSwapBuffers(window);
        glfwPollEvents();

        last_time = current_time;
        ++fps_counter;
    }

    std::cout << "FPS:\t" << fps_counter / glfwGetTime();
    glfwTerminate();
    return 0;
}
