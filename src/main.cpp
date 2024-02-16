#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <math.h>
#include <list>
#include <iterator>
#include <memory>

#include "Classes/Object.h"

class Square :public Object 
{
public: 
    Square() :Object(true, false, 10, 4, 0.5, 0, 0.9) {
    }
};

class Floor: public Object 
{
public:
    Floor():Object(true, true, 1000, 4, 2, 0, -1) {        
    }
};
class Ball :public Object
{
public:
    Ball() :Object(true, false, 1, 50, 0.1, -0.5, 0.9) {
    }
};
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
    Floor floor;
    std::unique_ptr<Object> squarePtr(new Square());
    Ball ball;
    int fpsCounter = 0;
    double lastTime = glfwGetTime();
    glfwSwapInterval(1);
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
        if (currentTime > 2)
        {
            squarePtr.reset();
        }
    }
    glfwTerminate();
    std::cout << fpsCounter << std::endl;
    return 0;
}
