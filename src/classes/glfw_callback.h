#ifndef SIMULATION_CLASSES_GLFW_CALLBACK_H_
#define SIMULATION_CLASSES_GLFW_CALLBACK_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void EdgePan(GLFWwindow* window, float& delta_time);

#endif //SIMULATION_CLASSES_GLFW_CALLBACK_H_