#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "classes/Object.h"
#include "classes/ObjectShapes.h"

#include <iostream>

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

    Rectangle floor(true, true, 0, -0.8f, 1.0f, 2.0f);
    Rectangle floo2r(true, false, 0, 0.5f, 1.0f/2, 1.0f/2);
    Rectangle fl89oo2r(true, false, -0.5, 0.0f, 2.0f / 2, 1.0f / 2);
    Circle dadad(true, false, 1.0f, 0, 1.0f/5);
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
