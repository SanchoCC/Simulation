#ifndef SIMULATION_CLASSES_GLFW_CALLBACK_H_
#define SIMULATION_CLASSES_GLFW_CALLBACK_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void EdgePan(GLFWwindow* window, float& delta_time);
glm::vec3 UnProject(const glm::vec3& win, const glm::mat4& model, const glm::mat4& proj, const glm::vec4& viewport);
glm::vec2 GetCursorWorldPosition(GLFWwindow* window);

#endif //SIMULATION_CLASSES_GLFW_CALLBACK_H_