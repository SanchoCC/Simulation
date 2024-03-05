#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "classes/Object.h"
#include "classes/ObjectShapes.h"

#include <iostream>
#include <memory>

int Width = 1920;
int Height = 1080;
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
    // OpenGL (3.1)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
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
    //
    Rectangle floor(true, true, 0, -1.3f, 3.0f, 1.0f); 
    
    Rectangle box0(true, false, 0, 0.5f, 0.5f, 0.5f);
    Rectangle box1(true, false, -1, 0.35f, 0.5f, 0.5f);
    Rectangle box2(true, false, 0, -1.5f, 0.3f, 1);
    Rectangle box3(true, false, 1, 0.5f, 0.1, 0.5f);
    

    floor->SetMass(99999999999.0f);
    floor->SetTension(0.4f);
    box0->SetVelocityY(-100);
    box1->SetVelocityY(250);
    box3->SetVelocityY(-500);
    //
    double lastTime = glfwGetTime();
    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
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
