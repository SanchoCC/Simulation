#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "classes/Object.h"
#include "classes/ObjectShapes.h"

#include <iostream>

int Width = 800;
int Height = 600;
float KoefScreen = static_cast<float>(Width) / Height;
int fpsCounter = 0;

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
    double lastTime = glfwGetTime();
    glfwSwapInterval(1);
    //
    Rectangle floor(true, true, 0, -1.0f, 3.0f, 1.0f);
    Rectangle box(true, false, 0, 0.5f, 0.5f, 0.5f);
    Rectangle box2(true, false, 0.3f, 2.5f, 1.0f, 0.5f);
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
    std::cout << "FPS:\t" << fpsCounter / glfwGetTime();
    glfwTerminate(); 
    return 0;
}
