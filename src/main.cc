#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "classes/object.h"
#include "classes/object_shapes.h"
#include "classes/object_handler.h"

int width = 1280;
int height = 720;
bool full_screen = false;
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
    if (full_screen) {
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
    glScalef(1/koef_screen, 1, 1);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1);

    ObjectHandler object_handler;
    //
    Rectangle floor(true, 0, -1.3f, 3.0f, 1.0f); 

    Rectangle box0(false, 0, 0.5f, 0.3f, 0.3f);
    Rectangle box2(false, 0.1, 1.5f, 0.5f, 0.5f);
    Rectangle box3(false, 1, 0.5f, 0.5f, 0.5f);
    Rectangle box4(false, 0, 2.5f, 0.1f, 0.5f);

    Circle circle1(true, -0.7f, -0.3, 0.3f);
    Circle circle2(false, -0.7f, 1.0f, 0.3f);

    floor->SetMass(99999999999.0f);
    floor->SetTension(0.2f);

    box0->SetVelocityY(500);
    box2->SetRotationAngle(3);
    box2->SetVelocityY(-400);
    box3->SetVelocityY(500);

    circle1->SetMass(99999999999.0f);
    circle2->SetVelocityY(-200);

    //
    double last_time = glfwGetTime();
    int fpsCounter = 0;

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);  

        double current_time = glfwGetTime();
        double delta_time = current_time - last_time;      

        object_handler.MainCycle(Object::GetObjectsList(), delta_time);

        glfwSwapBuffers(window);
        glfwPollEvents();

        last_time = current_time;       
        ++fpsCounter;       
    }    
    std::cout << "FPS:\t" << fpsCounter / glfwGetTime();
    glfwTerminate(); 
    return 0;
}
