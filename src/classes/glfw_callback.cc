#include "glfw_callback.h"

#include <cmath>

#include "settings.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {

	double x_pos, y_pos;
	glfwGetCursorPos(window, &x_pos, &y_pos);
	float x_world = 2 * (x_pos / Settings::GetInstance().screen_.width) - 1;
	float y_world = -2 * (y_pos / Settings::GetInstance().screen_.height) + 1;
	float k = 0.5f;
	float koef_screen = Settings::GetInstance().screen_.koef_screen;
	float scale = 1.f;
	
	if (yoffset > 0.0) {
		scale = 1.049;
	} else if (yoffset < 0.0) {
		scale = 0.953;
	}
	for (int i = 0; i < std::abs(std::round(yoffset)); ++i) {
		glTranslatef(-x_world * k, -y_world * k, 1.f);
		glScalef(scale, scale, 0);
	}
}

void CheckSimulationSpeed(GLFWwindow* window, float& delta_time) {	
	int state_space = glfwGetKey(window, GLFW_KEY_SPACE);
	if (state_space == GLFW_PRESS) {
		delta_time = 0.f;
	}
	int state_left = glfwGetKey(window, GLFW_KEY_LEFT);
	if (state_left == GLFW_PRESS) {
		delta_time *= 0.5f;
	}
	int state_right = glfwGetKey(window, GLFW_KEY_RIGHT);
	if (state_right == GLFW_PRESS) {
		delta_time *= 2.f;
	}
}

void EdgePan(GLFWwindow* window, float delta_time) {
	double x_pos, y_pos;
	glfwGetCursorPos(window, &x_pos, &y_pos);

	double width = Settings::GetInstance().screen_.width;
	double height = Settings::GetInstance().screen_.height;
	double threshold_x = width * 0.1;
	double threshold_y = height * 0.1;
	double threshold_x_closest = width * 0.03;
	double threshold_y_closest = height * 0.03;
	float delta_time_2 = delta_time + delta_time;

	if (x_pos > width - threshold_x_closest) {
		glTranslatef(-delta_time_2, 0, 0);
	} else if (x_pos < 0.0 + threshold_x_closest) {
		glTranslatef(delta_time_2, 0, 0);
	} else if (x_pos > width - threshold_x) {
		glTranslatef(-delta_time, 0, 0);
	} else if (x_pos < 0.0 + threshold_x) {
		glTranslatef(delta_time, 0, 0);
	}
	if (y_pos > height - threshold_y_closest) {
		glTranslatef(0, delta_time_2, 0);
	} else if (y_pos < 0.0 + threshold_y_closest) {
		glTranslatef(0, -delta_time_2, 0);
	} else if (y_pos > height - threshold_y) {
		glTranslatef(0, delta_time, 0);
	} else if (y_pos < 0.0 + threshold_y) {
		glTranslatef(0, -delta_time, 0);
	}
}

