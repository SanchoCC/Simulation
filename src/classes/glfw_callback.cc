#include "glfw_callback.h"

#include <cmath>
#include <iostream>
#include <vector>

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
	

	if (yoffset > 0.0) {
		glTranslatef(-x_world * k / koef_screen, -y_world * k, 0);

		for (int i = 0; i < std::round(yoffset); ++i) {
			glScalef(1.1, 1.1, 0);
		}
	} else if (yoffset < 0.0) {		
		for (int i = 0; i < std::abs(std::round(yoffset)); ++i) {
			glScalef(0.9, 0.9, 0);
		}		
	}
}

void EdgePan(GLFWwindow* window) {
	double x_pos, y_pos;
	glfwGetCursorPos(window, &x_pos, &y_pos);

	double width = Settings::GetInstance().screen_.width;
	double height = Settings::GetInstance().screen_.height;
	double threshold_x = width * 0.12;
	double threshold_y = height * 0.12;
	double threshold_x_closest = width * 0.02;
	double threshold_y_closest = height * 0.02;

	if (x_pos > width - threshold_x_closest) {
		glTranslatef(-Settings::GetInstance().state_.delta_time * 2, 0, 0);
	} else if (x_pos < 0.0 + threshold_x_closest) {
		glTranslatef(Settings::GetInstance().state_.delta_time * 2, 0, 0);
	} else if (x_pos > width - threshold_x) {
		glTranslatef(-Settings::GetInstance().state_.delta_time, 0, 0);
	} else if (x_pos < 0.0 + threshold_x) {
		glTranslatef(Settings::GetInstance().state_.delta_time, 0, 0);
	}
	if (y_pos > height - threshold_y_closest) {
		glTranslatef(0, Settings::GetInstance().state_.delta_time * 2, 0);
	} else if (y_pos < 0.0 + threshold_y_closest) {
		glTranslatef(0, -Settings::GetInstance().state_.delta_time * 2, 0);
	} else if (y_pos > height - threshold_y) {
		glTranslatef(0, Settings::GetInstance().state_.delta_time, 0);
	} else if (y_pos < 0.0 + threshold_y) {
		glTranslatef(0, -Settings::GetInstance().state_.delta_time, 0);
	}	
}

