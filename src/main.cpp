#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <math.h>
#include <list>
#include <iterator>
#include <memory>

#include "classes/Object.h"
#include "classes/ObjectShapes.h"

int Width = 800;
int Height = 600;
float KoefScreen = static_cast<float>(Width) / Height;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    // GLFW
    if (!glfwInit()) {
        std::cerr << "glfwInit error" << std::endl;
        return -1;
    }

    // OpenGL (4.6)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    GLFWwindow* window = glfwCreateWindow(Width, Height, "Hello, OpenGL!", nullptr, nullptr);
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
    glScalef(1/KoefScreen, 1, 1);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 
    
    int fpsCounter = 0;
    double lastTime = glfwGetTime();
    glfwSwapInterval(1);
    //
    Circle ball(0, 0, 0.0, 0.5, 0.5);
    //
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);        
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;      
        Object::ObjectsMain(deltaTime);
        glfwSwapBuffers(window);
        glfwPollEvents();
        lastTime = currentTime;       
        ++fpsCounter;       
    }
    std::cout << fpsCounter << std::endl;
    std::cout << fpsCounter / glfwGetTime();
    glfwTerminate(); 
    return 0;
}
