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

    //   
    Rectangle floor(1, 0, -5.8f, 10.0f, 11.0f);
    Circle circle0(0, -0.5, 0.5, 0.2);
    Circle circle1(0, -1.3, 0.4, 0.3);
    Circle circle2(0, 0.7, 0.5, 0.2);
    Circle circle3(0, 1.3, 0.2, 0.15);
    Circle circle4(1, 0.0, 0.45, 0.2);
    circle0.SetAngularVelocity(-6.0);
    circle1.SetVelocity(glm::vec2(0.7, 0));
    circle3.SetAngularVelocity(14.0);
    //

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
