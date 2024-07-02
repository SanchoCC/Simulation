#include "glfw_callback.h"

#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	if (yoffset > 0.0) {
		for (int i = 0; i < std::round(yoffset); ++i) {
			glScalef(1.1, 1.1, 0);
		}
	} else if (yoffset < 0.0) {
		for (int i = 0; i < std::abs(std::round(yoffset)); ++i) {
			glScalef(0.9, 0.9, 0);
		}
	}
}
