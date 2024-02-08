#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <math.h>
#include <list>
#include <iterator>

#include "Classes/Object.h"

const double g = -9.8/10;

class Square :public Object 
{
public: 
    Square() :Object(true, false, 10, 4, 0.5, 0, 0.9) {

    }
    ~Square() {
    }
};

class Floor: public Object 
{
public:
    Floor():Object(true, true, 1000, 4, 2, 0, -1) {
        
    }

    ~Floor() {


    }

private:

};
class Ball :public Object
{
public:
    Ball() :Object(true, false, 1, 50, 0.1, -0.5, 0.9) {

    }
    ~Ball() {
    }
};



int Width = 800;
int Height = 600;
float KoefScreen = static_cast<float>(Width) / Height;

// Обработчик событий изменения размера окна
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    // Инициализация GLFW
    if (!glfwInit()) {
        std::cerr << "glfwInit error" << std::endl;
        return -1;
    }

    // Устанавливаем версию OpenGL (3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    // Создаем окно
    GLFWwindow* window = glfwCreateWindow(Width, Height, "Hello, OpenGL!", nullptr, nullptr);
    if (!window) {
        std::cerr << "glfwCreateWindow error" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Делаем текущим контекст окна
    glfwMakeContextCurrent(window);

    // Инициализация Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Ошибка инициализации Glad" << std::endl;
        glfwTerminate();
        return -1;
    }
       

    glScalef(1/KoefScreen, 1, 1);

    // Устанавливаем обработчик изменения размера окна
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // Создаем экземпляр класса для отрисовки пола

    std::list<Object> ObjectsList;
    Floor floor;
    ObjectsList.push_back(floor);
    Square square;
    ObjectsList.push_back(square);
    Square square1;
    
    
    
    

    int fpsCounter = 0;
    double lastTime = glfwGetTime();
    glfwSwapInterval(1);
    // Основной цикл
    while (!glfwWindowShouldClose(window)) {
        // Очистка экрана (яркий серый цвет фона)
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
        // Отрисовка пола;
        for (auto it = ObjectsList.begin(); it != ObjectsList.end(); ++it) {
            it->Render();
            it->Move(0, g, deltaTime);
           
            auto inner_it = it;
            ++inner_it;  // Переходим к следующему элементу

            while (inner_it != ObjectsList.end()) 
            {
                auto inner_itAngles = inner_it->Angles.begin();
                while (inner_itAngles != inner_it->Angles.end())
                {
                    if (inner_itAngles->first <= it->Angles[0].first && inner_itAngles->second <= it->Angles[0].second &&
                        inner_itAngles->first >= it->Angles[1].first && inner_itAngles->second <= it->Angles[1].second &&
                        inner_itAngles->first >= it->Angles[2].first && inner_itAngles->second >= it->Angles[2].second &&
                        inner_itAngles->first <= it->Angles[3].first && inner_itAngles->second >= it->Angles[3].second
                        )
                    {
                        it->VelocityY += -g/10;
                        inner_it->VelocityY += -g/10;
                        inner_itAngles = inner_it->Angles.end();
                        
                    }       
                    else
                    {
                        inner_itAngles++;
                    }
                }
                
                
                ++inner_it;  // Переходим к следующему элементу
            }
        }

        // Обмен буферов
        glfwSwapBuffers(window);

        // Проверка событий и вызов обработчиков
        glfwPollEvents();

        lastTime = currentTime;
        
        ++fpsCounter;
    }

    // Завершение работы
    glfwTerminate();
    std::cout << fpsCounter << std::endl;
    return 0;
}
